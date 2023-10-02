#include <QApplication>

#include "todolList.hpp"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    TODO::TODOList w;
    w.show();
    return a.exec();
}
