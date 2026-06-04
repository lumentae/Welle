#include <model/SongModel.h>
#include <QUrl>
#include <QDir>
#include <QtConcurrent>

namespace welle::model {
    SongModel::SongModel(QObject *parent) : QAbstractListModel(parent) {}

    int SongModel::rowCount(const QModelIndex &parent) const {
        return m_Songs.size();
    }

    QVariant SongModel::data(const QModelIndex &index, int role) const {
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

    QHash<int, QByteArray> SongModel::roleNames() const {
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

    void SongModel::setSongs(const QList<medialib::types::Song> &songs) {
        beginResetModel();
        m_Songs = songs;
        endResetModel();
    }

    void SongModel::play(const int index) const {
        if (index < 1 || index > m_Songs.size())
            return;

        const auto song = m_Songs.at(index - 1);
        qDebug() << "Playing song:" << QString::fromStdString(song.title);
    }

    void SongModel::appendSongs(const QList<medialib::types::Song> &songs) {
        beginInsertRows(QModelIndex(), m_Songs.size(), m_Songs.size() + songs.size() - 1);
        m_Songs.append(songs);
        endInsertRows();
        m_Offset += songs.size();

        m_IsLoading = false;
        emit isLoadingChanged();
    }

    void SongModel::setFetchNextPageCallback(const std::function<void(uint32_t, uint32_t)> &fetchNextPageCallback) {
        m_FetchNextPageCallback = fetchNextPageCallback;
    }

    void SongModel::fetchNextPage() {
        if (m_IsLoading || !m_HasMore || !m_FetchNextPageCallback) return;
        m_IsLoading = true;
        emit isLoadingChanged();
        QThreadPool::globalInstance()->start([this] {
            m_FetchNextPageCallback(m_Offset, m_PageSize);
        });
    }
}
