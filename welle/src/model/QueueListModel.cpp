#include <model/QueueListModel.h>
#include <QtConcurrent>

#include "Queue.h"
#include "audio/AudioPlayer.h"
#include "utility/Qt.h"

namespace welle::model {
    QueueListModel::QueueListModel(QObject *parent) : QAbstractListModel(parent) {}

    int QueueListModel::rowCount(const QModelIndex &parent) const {
        return m_Songs.size();
    }

    QVariant QueueListModel::data(const QModelIndex &index, int role) const {
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

    QHash<int, QByteArray> QueueListModel::roleNames() const {
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

    void QueueListModel::setSongs(const QList<medialib::types::Song> &songs) {
        beginResetModel();
        m_Songs = songs;
        endResetModel();
    }

    void QueueListModel::play(const int index) const {
        if (index < 1 || index > m_Songs.size())
            return;

        const auto song = m_Songs.at(index - 1);
        medialib::Queue::getInstance().playNow(utility::Qt::qListToVector(m_Songs), index - 1);
    }

    void QueueListModel::updateSongs() {
        auto& queue = medialib::Queue::getInstance();
        const auto queueSongs = queue.getQueue();
        const auto qlistSongs = utility::Qt::vectorToQList(queueSongs);
        setSongs(qlistSongs);

        emit songsChanged();
    }

    void QueueListModel::appendSongs(const QList<medialib::types::Song> &songs) {
        beginInsertRows(QModelIndex(), m_Songs.size(), m_Songs.size() + songs.size() - 1);
        m_Songs.append(songs);
        endInsertRows();
        m_Offset += songs.size();
        
        medialib::Queue::getInstance().addToQueue(utility::Qt::qListToVector(songs));
    }
}
