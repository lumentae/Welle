#include <iostream>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <qqmlcontext.h>

#include "PlayingSongModel.h"
#include "Queue.h"
#include "audio/AudioPlayer.h"
#include "client/OpenSubsonicClient.h"
#include "model/SongListModel.h"
#include "utility/Qt.h"

using namespace welle;

int main(int argc, char* argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    medialib::client::OpenSubsonicClient client(argv[1], argv[2], argv[3]);
    client.ping();

    medialib::audio::AudioPlayer::getInstance().initialize([&](const medialib::types::Song& song) {
        std::cout << "Downloading " << song.title << "..." << std::endl;
        client.downloadSong(song);
    });

    auto* songListModel = new model::SongListModel(&engine);
    auto* playingSongModel = new model::PlayingSongModel(&engine);
    engine.rootContext()->setContextProperty("songListModel", songListModel);
    engine.rootContext()->setContextProperty("playingSong", playingSongModel);
    engine.rootContext()->setContextProperty("primaryColor", "#0f0f0f");
    engine.rootContext()->setContextProperty("primaryColorSelected", "#333");
    engine.rootContext()->setContextProperty("primaryTextColor", "#e0e0e0");
    engine.rootContext()->setContextProperty("secondaryColor", "#050505");
    engine.rootContext()->setContextProperty("secondaryTextColor", "#666");
    engine.rootContext()->setContextProperty("accentColor", "#ff0000");
    engine.rootContext()->setContextProperty("borderColor", "#2a2a2a");

    engine.loadFromModule("welle", "Main");

    medialib::Queue::getInstance().setOnSongChanged([&](const medialib::types::Song& song) {
        std::cout << "Playing " << song.title << "..." << std::endl;
        medialib::audio::AudioPlayer::getInstance().play(song, false);
        playingSongModel->update();
    });

    songListModel->setFetchNextPageCallback([&](const uint32_t offset, const uint32_t count) {
        const auto newSongs = client.getSongs({
            .songCount = count,
            .songOffset = offset
        });
        songListModel->appendSongs(utility::Qt::vectorToQList(newSongs));
    });

    medialib::audio::AudioPlayer::getInstance().setAfterPlayCallback([&] {
        playingSongModel->update();
    });

    return QGuiApplication::exec();
}
