#include "model/PlayingSongModel.h"

#include <QDir>
#include <QUrl>

#include "audio/AudioPlayer.h"
#include "types/Song.h"

namespace welle::model {
    PlayingSongModel::PlayingSongModel(QObject *parent) : QObject(parent) {
        m_PollTimer = new QTimer(this);
        connect(m_PollTimer, &QTimer::timeout, this, [this] {
            auto& audioPlayer = audio::AudioPlayer::getInstance();
            if (ma_sound_is_playing(audioPlayer.sound())) {
                emit positionChanged();
            }
            if (audioPlayer.stopRequested())
                audioPlayer.stop();
        });
        m_PollTimer->start(100);
    }

    QString PlayingSongModel::title() {
        return QString::fromStdString(audio::AudioPlayer::getInstance().getCurrentlyPlayingSong().title);
    }

    QString PlayingSongModel::artist() {
        return QString::fromStdString(audio::AudioPlayer::getInstance().getCurrentlyPlayingSong().artist);
    }

    QString PlayingSongModel::album() {
        return QString::fromStdString(audio::AudioPlayer::getInstance().getCurrentlyPlayingSong().album);
    }

    QString PlayingSongModel::albumId() {
        return QString::fromStdString(audio::AudioPlayer::getInstance().getCurrentlyPlayingSong().albumId);
    }

    int PlayingSongModel::duration() {
        return audio::AudioPlayer::getInstance().getCurrentlyPlayingSong().duration;
    }

    float PlayingSongModel::position() {
        return audio::AudioPlayer::getInstance().position();
    }

    void PlayingSongModel::setPosition(const float position) {
        audio::AudioPlayer::getInstance().seek(position);
    }

    QUrl PlayingSongModel::coverArt() {
        const QString path = QDir::current().absoluteFilePath("cache/" + QString::fromStdString(audio::AudioPlayer::getInstance().getCurrentlyPlayingSong().coverArt));
        return QUrl::fromLocalFile(path);
    }

    QString PlayingSongModel::path() {
        return QString::fromStdString(audio::AudioPlayer::getInstance().getCurrentlyPlayingSong().path);
    }

    QString PlayingSongModel::suffix() {
        return QString::fromStdString(audio::AudioPlayer::getInstance().getCurrentlyPlayingSong().suffix);
    }

    int PlayingSongModel::playCount() {
        return audio::AudioPlayer::getInstance().getCurrentlyPlayingSong().playCount;
    }
}
