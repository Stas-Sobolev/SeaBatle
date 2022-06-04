#include "mainwindow.h"
#include <QGraphicsScene>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGraphicsScene* scene = new QGraphicsScene(0,0,720,630);
    MainWindow w(scene);

    w.show();
    return a.exec();
}
