#include "mainwindow.h"
#include <QDebug>
#include <QDebug>
#include <QGridLayout>
#include <QGridLayout>
#include <QPaintEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QPainter>
#include <QString>
#include <QWidget>
#include "./ui_mainwindow.h"
#define cout qDebug()
#include <QHBoxLayout>
#include <QPushButton>
#include <QScrollArea>
#include "dishui.h"
#include "floatpan.h"
#include "qmylabel.h"
#include "newdishui.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    ui->setupUi(this);

    //ui->scrollAreaWidgetContents->installEventFilter(this);
    //ui->scrollArea->setWidgetResizable(true);   //使scrollerea可滚动
    //setCentralWidget(ui->scrollArea);
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(&_dishDetailUI);
    ui->dishDetailUIContainer->setLayout(layout);
}

MainWindow::~MainWindow(){
    delete ui;
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event){
    //if (watched == ui->scrollAreaWidgetContents && event->type() == QEvent::Paint) {
    //paintWidget(dishDataLoader.curDishes);
    //}

    //return QWidget::eventFilter(watched, event);
}

void MainWindow::paintEvent(QPaintEvent *) //画背景图
{
    QPainter p(this); //创建一个painter,指定窗口为画布

    p.drawPixmap(this->rect(), QPixmap("://background")); //画背景图
}

void MainWindow::paintWidget(QList<Dish> curDishes){
    //创建一个painter,指定窗口为scrollAreaWidgetContents
    //QPainter p1(ui->scrollAreaWidgetContents);

    // 添加若干张图片到布局中
    //dishDataLoader.filt(filter, nameCmp);
    for (int i = 0; i < dishDataLoader.curDishes.size(); ++i) {
        // 在scrollAreaWidgetContents上绘制图片
        //p1.drawPixmap(60, 100 + i * 70, 480, 60, QPixmap(QDir::currentPath() + dishDataLoader.curDishes[i].img_path));
        //qDebug() << QDir::currentPath() + dishDataLoader.curDishes[i].img_path;
        /*QMyLabel *myLabel = new QMyLabel(ui->scrollAreaWidgetContents);
        myLabel->setFixedSize(480, 60);
        myLabel->setStyleSheet("background-color: rgba(255, 255, 255, 0);"); // 设置透明背景
        myLabel->move(60, 100 + i * 70);
        floatpan *widget = new floatpan();
        widget->setCustomText(QString::fromLocal8Bit("测试\r\ntest\r\n测试"));

        connect(myLabel, &QMyLabel::show, [=]() {
            // 悬浮窗显示处理
            myLabel->show();
        });

        connect(myLabel, &QMyLabel::hide, [=]() {
            // 悬浮窗隐藏处理
            myLabel->hide();
        });*/
    }

    //f(dishNum > 7){
    //ui->scrollAreaWidgetContents->setMinimumSize(0, 600 + (dishNum - 7) * 70);    //改变小widget的大小
    //}
}

void MainWindow::mousePressEvent(QMouseEvent *e){
    qDebug() << e->pos();
}

void MainWindow::on_search_clicked(){
    keyWord = ui->textEdit->toPlainText();

    updateDishUI();
}

void MainWindow::on_priceSlider_valueChanged(int value){
    qDebug() << "price slider value changed to:" << value;
    Mprice = value == 100 ? value : value * 0.4;
    if (Mprice < 100 and Mprice > 0) {
        ui->priceBoundLabel->setText((std::to_string(Mprice) + ("元以下")).c_str());
    } else if (Mprice == 100) {
        ui->priceBoundLabel->setText("任意价格");
    } else {
        ui->priceBoundLabel->setText("0元购");
    }

    ui->priceBoundLabel->setAlignment(Qt::AlignCenter);

    updateDishUI();
}

void MainWindow::updateDishUI(){
    // 先按条件过滤和排序菜品

    if (keyWord == "") {
        // 没有搜索内容时就按价格排序
        dishDataLoader.filt(Filter(Mprice, matchLabels, unmatchLabels), priceCmp);
    } else {
        // 有搜索内容时就按相似度排序
        dishDataLoader.filt(Filter(Mprice, matchLabels, unmatchLabels), similarityCmp(keyWord));
    }

    // TODO: 绘制菜品
    QVBoxLayout *vLayout = new QVBoxLayout();
    //vLayout->size
    QWidget *qwgt = new QWidget();
    for (auto d : dishDataLoader.curDishes) {
        DishUI *dishUI = new DishUI(this);
        dishUI->update(d);
        vLayout->addWidget(dishUI);
        connect(dishUI, &DishUI::dishUIClicked, &_dishDetailUI, &dishDetailUI::update);
        connect(dishUI, &DishUI::dishUIDelete, this, &MainWindow::rmv_dish);
    }
    qwgt->setLayout(vLayout);
    ui->dishScrollArea->setWidget(qwgt);
}

void MainWindow::rmv_dish(Dish& d) {
    dishDataLoader.removeDish(d);
    updateDishUI();
}

void MainWindow::add_matchLabel(QString label){
    // 避免重复
    if (matchLabels.contains(label))
        return;

    matchLabels.append(label);

    updateDishUI();
}

void MainWindow::rmv_matchLabel(QString label){
    if (not matchLabels.contains(label))
        return;

    matchLabels.removeAll(label);

    updateDishUI();
}

// 家园一层
void MainWindow::on_flavor_yes_stateChanged(int arg1){
    QString lbl = "家园一层";
    if (arg1 == 0) {
        rmv_matchLabel(lbl);
    } else {
        add_matchLabel(lbl);
    }
}

// 家园2层
void MainWindow::on_checkBox_stateChanged(int arg1)
{
    QString lbl = "家园二层";
    if (arg1 == 0) {
        rmv_matchLabel(lbl);
    } else {
        add_matchLabel(lbl);
    }
}

// jia 3
void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    QString lbl = "家园三层";
    if (arg1 == 0) {
        rmv_matchLabel(lbl);
    } else {
        add_matchLabel(lbl);
    }
}

// jia 4
void MainWindow::on_flavor_no_stateChanged(int arg1)
{
    QString lbl = "家园四层";
    if (arg1 == 0) {
        rmv_matchLabel(lbl);
    } else {
        add_matchLabel(lbl);
    }
}

// nong yuan 1f

void MainWindow::on_flavor_no_2_stateChanged(int arg1)
{
    QString lbl = "农园一层";
    if (arg1 == 0) {
        rmv_matchLabel(lbl);
    } else {
        add_matchLabel(lbl);
    }
}

void MainWindow::on_flavor_no_3_stateChanged(int arg1)
{
    QString lbl = "农园二层";
    if (arg1 == 0) {
        rmv_matchLabel(lbl);
    } else {
        add_matchLabel(lbl);
    }
}

// 学一

void MainWindow::on_flavor_yes_2_stateChanged(int arg1)
{
    QString lbl = "学一食堂";
    if (arg1 == 0) {
        rmv_matchLabel(lbl);
    } else {
        add_matchLabel(lbl);
    }
}

// 学五

void MainWindow::on_flavor_yes_3_stateChanged(int arg1)
{
    QString lbl = "学五食堂";
    if (arg1 == 0) {
        rmv_matchLabel(lbl);
    } else {
        add_matchLabel(lbl);
    }
}


void MainWindow::add_dish(Dish& d) {
    this->dishDataLoader.addDish(d);
    qDebug() << "add dish" << d.name;
    updateDishUI();
}

// add dish
int MainWindow::show_add_dishUI() {

    NewDishUI newDishUI(this);
    connect(&newDishUI, &NewDishUI::dishAddComplete, this, &MainWindow::add_dish);
    newDishUI.setWindowTitle("添加新菜品");
    newDishUI.show();

    return newDishUI.exec();
}
void MainWindow::on_pushButton_clicked()
{
    hide();
    this->show_add_dishUI();
    show();
}


void MainWindow::on_flavor_no_4_stateChanged(int arg1)
{
    QString lbl = "米饭";
    if (arg1 == 0) {
        rmv_matchLabel(lbl);
    } else {
        add_matchLabel(lbl);
    }
}


void MainWindow::on_flavor_no_5_stateChanged(int arg1)
{
    QString lbl = "面食";
    if (arg1 == 0) {
        rmv_matchLabel(lbl);
    } else {
        add_matchLabel(lbl);
    }
}


void MainWindow::on_flavor_no_6_stateChanged(int arg1)
{
    QString lbl = "鱼粉";
    if (arg1 == 0) {
        rmv_matchLabel(lbl);
    } else {
        add_matchLabel(lbl);
    }
}


void MainWindow::on_flavor_no_10_stateChanged(int arg1)
{
    QString lbl = "清淡";
    if (arg1 == 0) {
        rmv_matchLabel(lbl);
    } else {
        add_matchLabel(lbl);
    }
}


void MainWindow::on_flavor_no_7_stateChanged(int arg1)
{
    QString lbl = "微辣";
    if (arg1 == 0) {
        rmv_matchLabel(lbl);
    } else {
        add_matchLabel(lbl);
    }
}


void MainWindow::on_flavor_no_8_stateChanged(int arg1)
{
    QString lbl = "特辣";
    if (arg1 == 0) {
        rmv_matchLabel(lbl);
    } else {
        add_matchLabel(lbl);
    }
}


void MainWindow::on_flavor_no_9_stateChanged(int arg1)
{
    QString lbl = "";
    if (arg1 == 0) {
        rmv_matchLabel(lbl);
    } else {
        add_matchLabel(lbl);
    }
}

