#pragma once

#include <QObject>
#include <QUrl>
#include <QTimer>
#include <QtQml/qqmlregistration.h>

namespace welle::model {
    class PlayingSongModel : public QObject {
        Q_OBJECT

    public:
        explicit PlayingSongModel(QObject* parent = nullptr);

        Q_PROPERTY(QString title READ title NOTIFY songChanged)
        Q_PROPERTY(QString artist READ artist NOTIFY songChanged)
        Q_PROPERTY(QString album READ album NOTIFY songChanged)
        Q_PROPERTY(QString albumId READ albumId NOTIFY songChanged)
        Q_PROPERTY(int duration READ duration NOTIFY songChanged)
        Q_PROPERTY(QUrl coverArt READ coverArt NOTIFY songChanged)
        Q_PROPERTY(QString path READ path NOTIFY songChanged)
        Q_PROPERTY(QString suffix READ suffix NOTIFY songChanged)
        Q_PROPERTY(int playCount READ playCount NOTIFY songChanged)
        Q_PROPERTY(float position READ position NOTIFY positionChanged)
        Q_PROPERTY(bool paused READ paused NOTIFY pausedChanged)

        static QString title();
        static QString artist();
        static QString album();
        static QString albumId();
        static int duration();
        static QUrl coverArt();
        static QString path();
        static QString suffix();
        static int playCount();
        static float position();
        static bool paused();

        void update() { emit songChanged(); emit positionChanged(); emit pausedChanged(); }

        Q_INVOKABLE static void setPosition(float position);
        Q_INVOKABLE void playOrPause();
        Q_INVOKABLE static void next();
        Q_INVOKABLE static void previous();

        signals:
            void songChanged();
            void positionChanged();
            void pausedChanged();

        private:
            QTimer* m_PollTimer;
    };
}