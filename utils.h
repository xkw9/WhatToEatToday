#ifndef UTILS_H
#define UTILS_H

#endif // UTILS_H

#include "Dish.h"
// if not
// 按价格给Dish排序
inline bool priceCmp(const Dish &d1, const Dish &d2)
{
    if (d1.price == d2.price) {
        return d1.name < d2.name;
    } else {
        return d1.price < d2.price;
    }
}

// 按名字给Dish排序
inline bool nameCmp(const Dish &d1, const Dish &d2)
{
    if (d1.name == d2.name) {
        return d1.price < d2.price;
    } else {
        return d1.name < d2.name;
    }
}

// 计算Dish与keyWord相似度
inline double calcSimilarity(const Dish &d, const QString &keyWord)
{
    // 目前计算的方法是：看Dish.name和Labels与keyWord有几个共同字符
    int repeatedChar = 0;
    for (QChar c : keyWord) {
        if (d.name.contains(c)) {
            repeatedChar++;
        }

        for (auto label : d.labels) {
            if (label.contains(c)) {
                repeatedChar++;
            }
        }
    }
    return repeatedChar;
}

// 按搜索关键字相似度给Dish排序
class similarityCmp
{
    QString keyWord = "";

public:
    similarityCmp(QString &keyWord)
        : keyWord(keyWord)
    {}

    bool operator()(const Dish &d1, const Dish &d2)
    {
        return calcSimilarity(d1, keyWord) > calcSimilarity(d2, keyWord);
    }
};

// 条件过滤器
class Filter
{
    // 最高价格
    double Mprice = 100000;
    //  必须至少符合一个的Label
    QList<QString> matchLabels = {};
    //  必须不包含的Label
    QList<QString> unmatchLabels = {};

public:
    Filter(double Mprice = 100000,
           QList<QString> matchLabels = {},
           QList<QString> unmatchLabels = {})
    {
        this->Mprice = Mprice;
        this->matchLabels = matchLabels;
        this->unmatchLabels = unmatchLabels;
    }

    // 判断Dish是否被过滤，不符合条件的返回true
    bool operator()(Dish &d)
    {
        if (d.price > Mprice)
            return true;

        for (auto label : unmatchLabels) {
            if (d.labels.contains(label)) {
                return true;
            }
        }

        // 为空说明没有限制
        if (matchLabels.empty())
            return false;

        for (auto label : matchLabels) {
            // 只要符合一个就行了!
            if (d.labels.contains(label)) {
                return false;
            }
        }

        return true;
    }
};
