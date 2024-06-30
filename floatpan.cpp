#include "floatpan.h"
#include "ui_floatpan.h"

floatpan::floatpan(QWidget *parent, QString text)
    : QWidget(parent)
    , ui(new Ui::floatpan)
{
    ui->setupUi(this);
    ui->textEdit->setText(text);
    QFont font;
    font.setPixelSize(20);
    font.setBold(true);
    ui->textEdit->setFont(font);
    setStyleSheet("background-color: rgba(255, 255, 255, 255);");
    ui->textEdit->setStyleSheet("background-color: rgba(255, 255, 255, 255);");
}

floatpan::~floatpan()
{
    delete ui;
}

void floatpan::setCustomText(QString text)
{
    ui->textEdit->setText(text);
}
