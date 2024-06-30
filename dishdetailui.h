#ifndef DISHDETAILUI_H
#define DISHDETAILUI_H

#include <QWidget>
#include "Dish.h"

namespace Ui {
class dishDetailUI;
}

class dishDetailUI : public QWidget
{
    Q_OBJECT

public:
    explicit dishDetailUI(QWidget *parent = nullptr);
    ~dishDetailUI();

public slots:
    void update(Dish &d);

private:
    Ui::dishDetailUI *ui;
};

#endif // DISHDETAILUI_H
