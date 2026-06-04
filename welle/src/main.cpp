#include <iostream>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <qqmlcontext.h>

#include "client/OpenSubsonicClient.h"
#include "model/SongModel.h"
#include "utility/Qt.h"

using namespace welle;

int main(int argc, char* argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    auto* songModel = new model::SongModel(&engine);
    engine.rootContext()->setContextProperty("songModel", songModel);

    engine.loadFromModule("welle", "Main");

    medialib::client::OpenSubsonicClient client(argv[1], argv[2], argv[3]);
    client.ping();

    songModel->setFetchNextPageCallback([&](const uint32_t offset, const uint32_t count) {
        const auto newSongs = client.getSongs({
            .songCount = count,
            .songOffset = offset
        });
        songModel->appendSongs(utility::Qt::vectorToQList(newSongs));
    });

    return QGuiApplication::exec();
}
