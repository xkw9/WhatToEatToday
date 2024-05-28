#include "mainwindow.h"

#include <QApplication>
#include "DishData.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    DishData d;
    Dish dish;
    dish.name = "afff";
    dish.price = 1000;
    dish.description = "aaaaaaa!!";
    dish.img_path = "null";
    dish.labels = {"l1", "l3"};
    d.AddDish(dish);
    w.show();
    d.SaveDishData();
    return a.exec();
}
