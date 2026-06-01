#include <QApplication>
#include <QPushButton>

#include "client/SubsonicClient.h"

int main(int argc, char* argv[]) {
    //QApplication a(argc, argv);
    //QPushButton button("Hello world!", nullptr);
    //button.show();
    //return QApplication::exec();
    welle::medialib::SubsonicClient client(argv[1], argv[2], argv[3]);
    client.ping();
}
