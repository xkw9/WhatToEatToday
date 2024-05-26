#include "mainwindow.h"

#include <QApplication>
#include "DishData.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    DishData d;
    w.show();
    return a.exec();
}
