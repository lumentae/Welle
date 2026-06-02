#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "client/OpenSubsonicClient.h"

int main(int argc, char* argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.loadFromModule("welle", "Main");

    welle::medialib::OpenSubsonicClient client(argv[1], argv[2], argv[3]);
    client.ping();
    client.getSongs({
        .artistCount = 0,
        .albumCount = 0,
        .songCount = 1,
    });

    return QGuiApplication::exec();
}
