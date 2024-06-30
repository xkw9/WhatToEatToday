#ifndef FLOATPAN_H
#define FLOATPAN_H

#include <QWidget>

namespace Ui {
class floatpan;
}

class floatpan : public QWidget
{
    Q_OBJECT

public:
    explicit floatpan(QWidget *parent = nullptr, QString text = "default");
    ~floatpan();

    void setCustomText(QString text); //设置悬浮窗文字

private:
    Ui::floatpan *ui;
};

#endif // FLOATPAN_H
