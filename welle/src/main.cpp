#include <iostream>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <qqmlcontext.h>

#include "audio/AudioPlayer.h"
#include "client/OpenSubsonicClient.h"
#include "model/SongModel.h"
#include "utility/Qt.h"

using namespace welle;

int main(int argc, char* argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    medialib::client::OpenSubsonicClient client(argv[1], argv[2], argv[3]);
    client.ping();

    audio::AudioPlayer::getInstance().initialize([&](const medialib::types::Song& song) {
        std::cout << "Downloading " << song.title << "..." << std::endl;
        client.downloadSong(song);
    });

    auto* songModel = new model::SongModel(&engine);
    engine.rootContext()->setContextProperty("songModel", songModel);
    engine.rootContext()->setContextProperty("primaryColor", "#0f0f0f");
    engine.rootContext()->setContextProperty("primaryColorSelected", "#333");
    engine.rootContext()->setContextProperty("primaryTextColor", "#e0e0e0");
    engine.rootContext()->setContextProperty("secondaryColor", "#050505");
    engine.rootContext()->setContextProperty("secondaryTextColor", "#666");
    engine.rootContext()->setContextProperty("accentColor", "#ff0000");
    engine.rootContext()->setContextProperty("borderColor", "#2a2a2a");

    engine.loadFromModule("welle", "Main");

    songModel->setFetchNextPageCallback([&](const uint32_t offset, const uint32_t count) {
        const auto newSongs = client.getSongs({
            .songCount = count,
            .songOffset = offset
        });
        songModel->appendSongs(utility::Qt::vectorToQList(newSongs));
    });

    return QGuiApplication::exec();
}
