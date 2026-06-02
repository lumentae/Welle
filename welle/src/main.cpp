#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QAbstractListModel>
#include <QAbstractItemModel>
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
    const auto songs = client.getSongs({
        .songCount = 20,
        .songOffset = 20
    });

    QList<medialib::types::Song> myList;
    myList.reserve(songs.size());
    std::ranges::copy(songs, std::back_inserter(myList));

    songModel->setSongs(myList);

    return QGuiApplication::exec();
}
