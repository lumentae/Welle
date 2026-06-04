#pragma once

#include <QAbstractItemModel>
#include <QAbstractListModel>
#include <QList>
#include <QtQml/qqmlregistration.h>
#include "types/Song.h"

namespace welle::model {
    class SongModel : public QAbstractListModel {
        Q_OBJECT
        QML_ELEMENT

    public:
        enum Roles {
            IdRole = Qt::UserRole + 1,
            IndexRole,
            TitleRole,
            ArtistRole,
            AlbumRole,
            AlbumIdRole,
            DurationRole,
            CoverArtRole,
            PathRole,
            SuffixRole,
            PlayCountRole,
        };

        explicit SongModel(QObject* parent = nullptr);

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
        QHash<int, QByteArray> roleNames() const override;

        Q_INVOKABLE void setSongs(const QList<medialib::types::Song>& songs);
        Q_INVOKABLE void play(int index) const;

    private:
        QList<medialib::types::Song> m_Songs;
    };
}
