#include <model/SongListModel.h>
#include <QtConcurrent>

#include "Queue.h"
#include "audio/AudioPlayer.h"
#include "utility/Qt.h"

namespace welle::model {
    SongListModel::SongListModel(QQmlApplicationEngine *engine, QueueListModel *queue_list_model) :
        QAbstractListModel(engine),
        m_QueueListModel(queue_list_model) {}

    int SongListModel::rowCount(const QModelIndex &parent) const {
        return m_Songs.size();
    }

    QVariant SongListModel::data(const QModelIndex &index, const int role) const {
        if (!index.isValid() || index.row() >= m_Songs.size())
            return {};

        const auto& song = m_Songs.at(index.row());
        switch (role) {
            case IdRole: return QString::fromStdString(song.id);
            case IndexRole: return index.row() + 1;
            case TitleRole: return QString::fromStdString(song.title);
            case ArtistRole: return QString::fromStdString(song.artist);
            case AlbumRole: return QString::fromStdString(song.album);
            case AlbumIdRole: return QString::fromStdString(song.albumId);
            case DurationRole: return static_cast<qlonglong>(song.duration);
            case CoverArtRole: {
                const QString path = QDir::current().absoluteFilePath("cache/" + QString::fromStdString(song.coverArt));
                return QUrl::fromLocalFile(path).toString();
            }
            case PathRole: return QString::fromStdString(song.path);
            case SuffixRole: return QString::fromStdString(song.suffix);
            case PlayCountRole: return static_cast<qlonglong>(song.playCount);
            default: return {};
        }
    }

    QHash<int, QByteArray> SongListModel::roleNames() const {
        return {
            { IdRole,        "songId"    },
            { IndexRole,     "songIndex" },
            { TitleRole,     "title"     },
            { ArtistRole,    "artist"    },
            { AlbumRole,     "album"     },
            { AlbumIdRole,   "albumId"   },
            { DurationRole,  "duration"  },
            { CoverArtRole,  "coverArt"  },
            { PathRole,      "path"      },
            { SuffixRole,    "suffix"    },
            { PlayCountRole, "playCount" },
        };
    }

    void SongListModel::setSongs(const QList<medialib::types::Song> &songs) {
        beginResetModel();
        m_Songs = songs;
        endResetModel();

        m_LoadedFromDatabase = true;
        m_Offset = m_Songs.size();
    }

    void SongListModel::play(const int index) const {
        if (index < 1 || index > m_Songs.size())
            return;

        const auto song = m_Songs.at(index - 1);
        medialib::Queue::getInstance().playNow(utility::Qt::qListToVector(m_Songs), index - 1);

        m_QueueListModel->updateSongs();
    }

    void SongListModel::addToQueue(const int index) {
        medialib::Queue::getInstance().addToQueue({m_Songs[index]}, true);
    }

    void SongListModel::appendSongs(const QList<medialib::types::Song> &songs) {
        beginInsertRows(QModelIndex(), m_Songs.size(), m_Songs.size() + songs.size() - 1);
        m_Songs.append(songs);
        endInsertRows();
        m_Offset += songs.size();
        
        medialib::Queue::getInstance().addToQueue(utility::Qt::qListToVector(songs));

        m_IsLoading = false;
        emit isLoadingChanged();

        m_QueueListModel->updateSongs();
    }

    void SongListModel::setFetchNextPageCallback(const std::function<void(uint32_t, uint32_t)> &fetchNextPageCallback) {
        m_FetchNextPageCallback = fetchNextPageCallback;
    }

    void SongListModel::fetchNextPage() {
        if (m_IsLoading || !m_HasMore || !m_FetchNextPageCallback) return;
        if (m_LoadedFromDatabase) {
            m_LoadedFromDatabase = false;
            return;
        }
        m_IsLoading = true;
        emit isLoadingChanged();
        QThreadPool::globalInstance()->start([this] {
            m_FetchNextPageCallback(m_Offset, m_PageSize);
        });
    }
}
