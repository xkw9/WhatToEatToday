#ifndef DISHDATALOADER_H
#define DISHDATALOADER_H

#endif // DISHDATALOADER_H

#include "DishData.h"

class DishDataLoader
{
    DishData data;

public:
    // 当前条件下排好序的菜品
    QList<Dish> curDishes = {};
    DishDataLoader() { data.LoadDishData(); }

    template<class Filter, class Sorter>
    void filt(Filter filter, Sorter sorter)
    {
        curDishes.clear();
        for (auto d : data.dishes) {
            if (filter(d))
                continue;

            curDishes.push_back(d);
        }

        sort(curDishes.begin(), curDishes.end(), sorter);
    }

    void reLoad()
    {
        data.LoadDishData();
    }

    void addDish(Dish& d) {
        data.AddDish(d);
    }

    void removeDish(Dish& d) {
        data.RemoveDish(d.name);
    }
};
