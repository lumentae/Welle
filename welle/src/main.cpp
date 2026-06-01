#include <QApplication>
#include <QPushButton>

#include "../../medialib/include/client/OpenSubsonicClient.h"

int main(int argc, char* argv[]) {
    //QApplication a(argc, argv);
    //QPushButton button("Hello world!", nullptr);
    //button.show();
    //return QApplication::exec();
    welle::medialib::OpenSubsonicClient client(argv[1], argv[2], argv[3]);
    client.ping();
    client.getSongs({
        .artistCount = 0,
        .albumCount = 0,
        .songCount = 1,
    });
}
