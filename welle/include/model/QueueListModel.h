#pragma once

#include <QAbstractItemModel>
#include <QAbstractListModel>
#include <QList>
#include <QtQml/qqmlregistration.h>

#include "audio/AudioPlayer.h"
#include "client/IClient.h"
#include "types/Song.h"

namespace welle::model {
    class QueueListModel : public QAbstractListModel {
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

        explicit QueueListModel(QObject* parent = nullptr);

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
        QHash<int, QByteArray> roleNames() const override;

        Q_INVOKABLE void setSongs(const QList<medialib::types::Song>& songs);
        Q_INVOKABLE void appendSongs(const QList<medialib::types::Song>& songs);
        Q_INVOKABLE void play(int index) const;
        Q_INVOKABLE void updateSongs();

        Q_PROPERTY(QString currentTitle READ currentTitle)
        Q_PROPERTY(QString currentArtist READ currentArtist)
        Q_PROPERTY(QString currentCoverArt READ currentCoverArt)
        static QString currentTitle() {
            return QString::fromStdString(medialib::audio::AudioPlayer::getInstance().getCurrentlyPlayingSong().title);
        }
        static QString currentArtist() {
            return QString::fromStdString(medialib::audio::AudioPlayer::getInstance().getCurrentlyPlayingSong().artist);
        }
        static QString currentCoverArt() {
            return QString::fromStdString(medialib::audio::AudioPlayer::getInstance().getCurrentlyPlayingSong().coverArt);
        }

        signals:
            void songsChanged();

    private:
        QList<medialib::types::Song> m_Songs;
        uint64_t m_Offset = 0;
    };
}
