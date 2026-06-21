#include "model/PlayingSongModel.h"

#include <QDir>
#include <QUrl>

#include "Queue.h"
#include "audio/AudioPlayer.h"
#include "audio/MprisServer.h"
#include "types/Song.h"

namespace welle::model {
    PlayingSongModel::PlayingSongModel(QObject *parent) : QObject(parent) {
        m_PollTimer = new QTimer(this);
        connect(m_PollTimer, &QTimer::timeout, this, [this] {
            auto& audioPlayer = medialib::audio::AudioPlayer::getInstance();
            if (ma_sound_is_playing(audioPlayer.sound())) {
                emit positionChanged();
                medialib::audio::MprisServer::update(audioPlayer.position(), false);
            }
            if (audioPlayer.stopRequested())
                audioPlayer.pause();
        });
        m_PollTimer->start(100);
    }

    QString PlayingSongModel::title() {
        return QString::fromStdString(medialib::audio::AudioPlayer::getInstance().getCurrentlyPlayingSong().title);
    }

    QString PlayingSongModel::artist() {
        return QString::fromStdString(medialib::audio::AudioPlayer::getInstance().getCurrentlyPlayingSong().artist);
    }

    QString PlayingSongModel::album() {
        return QString::fromStdString(medialib::audio::AudioPlayer::getInstance().getCurrentlyPlayingSong().album);
    }

    QString PlayingSongModel::albumId() {
        return QString::fromStdString(medialib::audio::AudioPlayer::getInstance().getCurrentlyPlayingSong().albumId);
    }

    int PlayingSongModel::duration() {
        return medialib::audio::AudioPlayer::getInstance().getCurrentlyPlayingSong().duration;
    }

    float PlayingSongModel::position() {
        return medialib::audio::AudioPlayer::getInstance().position();
    }

    bool PlayingSongModel::paused() {
        return !ma_sound_is_playing(medialib::audio::AudioPlayer::getInstance().sound());
    }

    QString PlayingSongModel::repeatMode() {
        switch (medialib::audio::AudioPlayer::getInstance().repeatMode()) {
        case medialib::audio::AudioPlayer::RepeatMode::Enabled:
            return "enabled";
        case medialib::audio::AudioPlayer::RepeatMode::One:
            return "one";
        default:
            return "disabled";
        }
    }

    void PlayingSongModel::setPosition(const float position) {
        const auto& audioPlayer = medialib::audio::AudioPlayer::getInstance();
        audioPlayer.seek(position);
        medialib::audio::MprisServer::update(audioPlayer.position(), true);
    }

    void PlayingSongModel::playOrPause() {
        if (auto& audioPlayer = medialib::audio::AudioPlayer::getInstance(); ma_sound_is_playing(audioPlayer.sound()))
            audioPlayer.pause();
        else if (!audioPlayer.getCurrentlyPlayingSong().id.empty())
            audioPlayer.play();
        emit pausedChanged();
    }

    void PlayingSongModel::next() {
        medialib::Queue::getInstance().next();
    }

    void PlayingSongModel::previous() {
        medialib::Queue::getInstance().previous();
    }

    void PlayingSongModel::shuffle() {
        medialib::Queue::getInstance().shuffle();
    }

    void PlayingSongModel::repeat() {
        switch (auto& audioPlayer = medialib::audio::AudioPlayer::getInstance(); audioPlayer.repeatMode()) {
            case medialib::audio::AudioPlayer::RepeatMode::Disabled:
                audioPlayer.setRepeatMode(medialib::audio::AudioPlayer::RepeatMode::Enabled);
                break;
            case medialib::audio::AudioPlayer::RepeatMode::Enabled:
                audioPlayer.setRepeatMode(medialib::audio::AudioPlayer::RepeatMode::One);
                break;
            case medialib::audio::AudioPlayer::RepeatMode::One:
                audioPlayer.setRepeatMode(medialib::audio::AudioPlayer::RepeatMode::Disabled);
                break;
        }
        emit repeatChanged();
    }

    QUrl PlayingSongModel::coverArt() {
        const QString path = QDir::current().absoluteFilePath("cache/" + QString::fromStdString(medialib::audio::AudioPlayer::getInstance().getCurrentlyPlayingSong().coverArt));
        return QUrl::fromLocalFile(path);
    }

    QString PlayingSongModel::path() {
        return QString::fromStdString(medialib::audio::AudioPlayer::getInstance().getCurrentlyPlayingSong().path);
    }

    QString PlayingSongModel::suffix() {
        return QString::fromStdString(medialib::audio::AudioPlayer::getInstance().getCurrentlyPlayingSong().suffix);
    }

    int PlayingSongModel::playCount() {
        return medialib::audio::AudioPlayer::getInstance().getCurrentlyPlayingSong().playCount;
    }
}
