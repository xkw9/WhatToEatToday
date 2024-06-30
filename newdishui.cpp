#include "newdishui.h"
#include "ui_newdishui.h"

#include <QFileDialog>

NewDishUI::NewDishUI(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NewDishUI)
{
    ui->setupUi(this);
}

NewDishUI::~NewDishUI()
{
    delete ui;
}

// dish name changed
void NewDishUI::on_lineEdit_textChanged(const QString &arg1)
{
    d.name = arg1;
}

// dish price changed
void NewDishUI::on_spinBox_valueChanged(int arg1)
{
    d.price = arg1;
}

// label changed

void NewDishUI::on_textEdit_textChanged()
{
    QString labelStr = ui->textEdit->toPlainText();
    QList<QString> labels = labelStr.split(' ');
    labels.removeAll(' ');

    d.labels = labels;
}

// select path

void NewDishUI::on_pushButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(
        this, tr("选择图片文件"), QCoreApplication::applicationFilePath(), tr("Image Files (*.jpg *.png)"));
    qDebug() << "path choose: "<< path;
    d.img_path = path;
}



void NewDishUI::on_buttonBox_accepted()
{
    // TODO: 判断输入是否符合要求

    emit dishAddComplete(d);
}

// description changed
void NewDishUI::on_textEdit_2_textChanged()
{
    d.description = ui->textEdit_2->toPlainText();
}

