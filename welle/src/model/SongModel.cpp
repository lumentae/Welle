#include <model/SongModel.h>
#include <QUrl>
#include <QDir>
#include <QDebug>

namespace welle::model {
    SongModel::SongModel(QObject *parent) : QAbstractListModel(parent) {}

    int SongModel::rowCount(const QModelIndex &parent) const {
        return m_Songs.size();
    }

    QVariant SongModel::data(const QModelIndex &index, int role) const {
        if (!index.isValid() || index.row() >= m_Songs.size())
            return {};

        const auto song = m_Songs.at(index.row());
        switch (role) {
            case IdRole: return QString::fromStdString(song.id);
            case IndexRole: return index.row() + 1;
            case TitleRole: return QString::fromStdString(song.title);
            case ArtistRole: return QString::fromStdString(song.artist);
            case AlbumRole: return QString::fromStdString(song.album);
            case AlbumIdRole: return QString::fromStdString(song.albumId);
            case DurationRole: return static_cast<qlonglong>(song.duration);
            case CoverArtRole: {
                QString path = QDir::current().absoluteFilePath("cache/" + QString::fromStdString(song.coverArt));
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
}
