#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QMainWindow>
#include <QWidget>
#include "DishDataLoader.h"
#include "dishdetailui.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int dishNum = 11;
    DishDataLoader dishDataLoader;
    int Mprice = 100;
    QList<QString> matchLabels = {}, unmatchLabels = {};
    QString keyWord; // 搜索关键字

protected:
    bool eventFilter(QObject *watched, QEvent *event); //事件过滤器
    void paintEvent(QPaintEvent *);                    //画背景图
    void paintWidget(QList<Dish> curDishes);           //画菜品
    void mousePressEvent(QMouseEvent *e);              //鼠标点击事件
    void updateDishUI();                               // 更新DishUI
    int show_add_dishUI();

private slots:
    void on_search_clicked();

    void on_priceSlider_valueChanged(int value);

    void add_matchLabel(QString label);

    void rmv_matchLabel(QString label);
    //void on_unmatchLabel_changed(QString label);

    void rmv_dish(Dish& d);

    void add_dish(Dish& d);

    void on_flavor_yes_stateChanged(int arg1);

    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_flavor_no_stateChanged(int arg1);

    void on_flavor_no_2_stateChanged(int arg1);

    void on_flavor_no_3_stateChanged(int arg1);

    void on_flavor_yes_2_stateChanged(int arg1);

    void on_flavor_yes_3_stateChanged(int arg1);

    void on_pushButton_clicked();

    void on_flavor_no_4_stateChanged(int arg1);

    void on_flavor_no_5_stateChanged(int arg1);

    void on_flavor_no_6_stateChanged(int arg1);

    void on_flavor_no_10_stateChanged(int arg1);

    void on_flavor_no_7_stateChanged(int arg1);

    void on_flavor_no_8_stateChanged(int arg1);

    void on_flavor_no_9_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    dishDetailUI _dishDetailUI;
};
#endif // MAINWINDOW_H
