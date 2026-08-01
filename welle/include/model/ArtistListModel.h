#pragma once

#include <QAbstractItemModel>
#include <QAbstractListModel>
#include <QList>
#include <qqmlapplicationengine.h>
#include <QtQml/qqmlregistration.h>

#include "QueueListModel.h"
#include "audio/AudioPlayer.h"
#include "client/IClient.h"
#include "types/Artist.h"

namespace welle::model {
    class ArtistListModel : public QAbstractListModel {
        Q_OBJECT
        QML_ELEMENT
        QML_UNCREATABLE("ArtistListModel should be created from C++")

    public:
        enum Roles {
            IdRole = Qt::UserRole + 1,
            IndexRole,
            NameRole,
            CoverArtRole,
            AlbumCountRole,
        };
        Q_ENUM(Roles)

        explicit ArtistListModel(QQmlApplicationEngine* engine);

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
        QHash<int, QByteArray> roleNames() const override;

        void set(const QList<medialib::types::Artist> &artists);
        void append(const QList<medialib::types::Artist> &artists);

        Q_INVOKABLE void setFetchNextPageCallback(const std::function<void(uint32_t, uint32_t)> &fetchNextPageCallback);
        Q_INVOKABLE void fetchNextPage();

        Q_PROPERTY(bool hasMore READ hasMore NOTIFY hasMoreChanged)
        Q_PROPERTY(bool isLoading READ isLoading NOTIFY isLoadingChanged)
        bool hasMore() const { return m_HasMore; }
        bool isLoading() const { return m_IsLoading; }

        signals:
            void hasMoreChanged();
            void isLoadingChanged();

    private:
        QList<medialib::types::Artist> m_Entries;
        std::function<void(uint32_t, uint32_t)> m_FetchNextPageCallback;
        int m_Offset = 0;
        int m_PageSize = 50;
        bool m_HasMore = true;
        bool m_IsLoading = false;
        bool m_LoadedFromDatabase = false;
    };
}
