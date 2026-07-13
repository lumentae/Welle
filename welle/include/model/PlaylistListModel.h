#pragma once

#include <QAbstractItemModel>
#include <QAbstractListModel>
#include <QList>
#include <qqmlapplicationengine.h>
#include <QtQml/qqmlregistration.h>

#include "client/IClient.h"

namespace welle::model {
    class PlaylistListModel : public QAbstractListModel {
        Q_OBJECT
        QML_ELEMENT
        QML_UNCREATABLE("PlaylistListModel should be created from C++")

    public:
        enum Roles {
            IdRole = Qt::UserRole + 1,
            NameRole,
            OwnerRole,
            CreatedRole,
            ChangedRole,
            SongCountRole,
            DurationRole
        };
        Q_ENUM(Roles)

        explicit PlaylistListModel(QQmlApplicationEngine* engine);

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
        QHash<int, QByteArray> roleNames() const override;

        void setPlaylists(const QList<medialib::types::Playlist>& playlists);

        signals:
            void playlistsChanged();

    private:
        QList<medialib::types::Playlist> m_Playlists;
    };
}
