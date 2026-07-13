#include <model/PlaylistListModel.h>
#include <QtConcurrent>

#include "Queue.h"
#include "audio/AudioPlayer.h"
#include "utility/Qt.h"

namespace welle::model {
    PlaylistListModel::PlaylistListModel(QQmlApplicationEngine *engine) : QAbstractListModel(engine) {}

    int PlaylistListModel::rowCount(const QModelIndex &parent) const {
        return m_Playlists.size();
    }

    QVariant PlaylistListModel::data(const QModelIndex &index, const int role) const {
        if (!index.isValid() || index.row() >= m_Playlists.size())
            return {};

        const auto& playlist = m_Playlists.at(index.row());
        switch (role) {
            case IdRole: return QString::fromStdString(playlist.id);
            case NameRole: return QString::fromStdString(playlist.name);
            case OwnerRole: return QString::fromStdString(playlist.owner);
            case CreatedRole: return QString::fromStdString(playlist.created);
            case ChangedRole: return QString::fromStdString(playlist.changed);
            case SongCountRole: return QString::number(playlist.songCount);
            case DurationRole: return QString::number(playlist.duration);
            default: return {};
        }
    }

    QHash<int, QByteArray> PlaylistListModel::roleNames() const {
        return {
            { IdRole, "id" },
            { NameRole, "name" },
            { OwnerRole, "owner" },
            { CreatedRole, "created" },
            { ChangedRole, "changed" },
            { SongCountRole, "songCount" },
            { DurationRole, "duration" },
        };
    }

    void PlaylistListModel::setPlaylists(const QList<medialib::types::Playlist> &playlists) {
        beginResetModel();
        m_Playlists = playlists;
        endResetModel();
        emit playlistsChanged();
    }
}
