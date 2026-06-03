#include <iostream>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <qqmlcontext.h>

#include "client/OpenSubsonicClient.h"
#include "model/SongModel.h"

using namespace welle;

int main(int argc, char* argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    auto* songModel = new model::SongModel(&engine);
    engine.rootContext()->setContextProperty("songModel", songModel);

    engine.loadFromModule("welle", "Main");

    medialib::client::OpenSubsonicClient client(argv[1], argv[2], argv[3]);
    client.ping();
    const auto albums = client.search3({
        .artistCount = 1,
        .albumCount = 1,
        .songCount = 0
    });

    std::cout << albums.dump(4) << std::endl;

    const auto songs = client.getSongs({
        .songCount = 100,
        .songOffset = 20
    });

    QList<medialib::types::Song> myList;
    myList.reserve(songs.size());
    std::ranges::copy(songs, std::back_inserter(myList));

    songModel->setSongs(myList);

    return QGuiApplication::exec();
}
