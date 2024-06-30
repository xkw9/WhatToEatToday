#ifndef NEWDISHUI_H
#define NEWDISHUI_H

#include <QDialog>
#include "Dish.h"
namespace Ui {
class NewDishUI;
}

class NewDishUI : public QDialog
{
    Q_OBJECT

public:
    explicit NewDishUI(QWidget *parent = nullptr);
    ~NewDishUI();

private slots:
    void on_lineEdit_textChanged(const QString &arg1);

    void on_spinBox_valueChanged(int arg1);

    void on_textEdit_textChanged();

    void on_pushButton_clicked();

    void on_buttonBox_accepted();

    void on_textEdit_2_textChanged();

signals:
    void dishAddComplete(Dish& d);

private:
    Ui::NewDishUI *ui;
    Dish d;
};

#endif // NEWDISHUI_H
