#include "model/PlayingSongModel.h"

#include <QDir>
#include <QUrl>

#include "audio/AudioPlayer.h"
#include "types/Song.h"

namespace welle::model {
    PlayingSongModel::PlayingSongModel(QObject *parent) : QObject(parent) {}

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

    QString PlayingSongModel::duration() {
        return QString::number(audio::AudioPlayer::getInstance().getCurrentlyPlayingSong().duration);
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
