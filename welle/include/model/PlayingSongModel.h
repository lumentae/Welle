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

        void update() { emit songChanged(); emit positionChanged(); }

        Q_INVOKABLE static void setPosition(float position);
        Q_INVOKABLE static void playOrPause();

        signals:
            void songChanged();
            void positionChanged();

        private:
            QTimer* m_PollTimer;
    };
}