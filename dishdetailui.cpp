#include "dishdetailui.h"
#include <QCoreApplication>
#include "ui_dishdetailui.h"

dishDetailUI::dishDetailUI(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::dishDetailUI)
{
    ui->setupUi(this);
}

dishDetailUI::~dishDetailUI()
{
    delete ui;
}

void dishDetailUI::update(Dish &d)
{
    qDebug() << "dishDetailUI update to:" << d.name;
    // 设置菜名
    ui->nameText->setText(d.name);
    ui->nameText->setFont(QFont("Arial", 30));
    // 设置价格
    ui->priceText->setText(to_string((int) d.price).c_str());
    ui->priceText->setFont(QFont("Arial", 20));

    QPixmap pixmap;
    // very stupid , but useful for now
    if (d.img_path.startsWith("/Resources/Images"))
        pixmap.load(QCoreApplication::applicationDirPath() + d.img_path);
    else
        pixmap.load(d.img_path);

    if (pixmap.isNull()) {
        qDebug() << "Can not find image at:" <<  d.img_path;
    } else {
        // 缩放图片
        pixmap = pixmap.scaled(180, 120);
        ui->imageLabel->setPixmap(pixmap);
    }
    QString labelsText = "";
    for (int i = 0; i < d.labels.count(); i++) {
        if (i % 2 == 1)
            labelsText += '#' + d.labels[i] + '\n';
        else {
            labelsText += '#' + d.labels[i] + " ";
        }
    }
    ui->labelText->setText(labelsText);

    ui->detailLabel->setText(d.description);
}
