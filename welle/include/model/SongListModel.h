#pragma once

#include <QAbstractItemModel>
#include <QAbstractListModel>
#include <QList>
#include <QtQml/qqmlregistration.h>

#include "audio/AudioPlayer.h"
#include "client/IClient.h"
#include "types/Song.h"

namespace welle::model {
    class SongListModel : public QAbstractListModel {
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

        explicit SongListModel(QObject* parent = nullptr);

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
        QHash<int, QByteArray> roleNames() const override;

        Q_INVOKABLE void setSongs(const QList<medialib::types::Song>& songs);
        Q_INVOKABLE void appendSongs(const QList<medialib::types::Song>& songs);
        Q_INVOKABLE void setFetchNextPageCallback(const std::function<void(uint32_t, uint32_t)> &fetchNextPageCallback);
        Q_INVOKABLE void fetchNextPage();
        Q_INVOKABLE void play(int index) const;

        Q_PROPERTY(bool hasMore READ hasMore NOTIFY hasMoreChanged)
        Q_PROPERTY(bool isLoading READ isLoading NOTIFY isLoadingChanged)
        Q_PROPERTY(QString currentTitle READ currentTitle)
        Q_PROPERTY(QString currentArtist READ currentArtist)
        Q_PROPERTY(QString currentCoverArt READ currentCoverArt)
        bool hasMore() const { return m_HasMore; }
        bool isLoading() const { return m_IsLoading; }
        static QString currentTitle() {
            return QString::fromStdString(audio::AudioPlayer::getInstance().getCurrentlyPlayingSong().title);
        }
        static QString currentArtist() {
            return QString::fromStdString(audio::AudioPlayer::getInstance().getCurrentlyPlayingSong().artist);
        }
        static QString currentCoverArt() {
            return QString::fromStdString(audio::AudioPlayer::getInstance().getCurrentlyPlayingSong().coverArt);
        }

        signals:
            void hasMoreChanged();
            void isLoadingChanged();
            void currentSongChanged();

    private:
        QList<medialib::types::Song> m_Songs;
        std::function<void(uint32_t, uint32_t)> m_FetchNextPageCallback;
        int m_Offset = 0;
        int m_PageSize = 50;
        bool m_HasMore = true;
        bool m_IsLoading = false;
    };
}
