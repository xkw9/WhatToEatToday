#ifndef DISH_H
#define DISH_H

#endif // DISH_H
#include <vector>

#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
using namespace std;

class Dish {
public:
    // 菜品名称
    QString name = "";

    // 菜品价格
    double price = 0;

    // 图片路径
    QString img_path = "";

    // 标签列表
    vector<QString> labels = {};

    // 介绍
    QString description = "";

    Dish(QJsonObject& jsonObj) {
        this->name = jsonObj.value("name").toString();
        this->price = jsonObj.value("price").toDouble();
        this->img_path = jsonObj.value("img_path").toString();
        this->description = jsonObj.value("description").toString();
        auto tmpArr = jsonObj.value("labels").toArray();
        for (auto element : tmpArr) {
            this->labels.push_back(element.toString());
        }

    }

    Dish() {

    }

    QJsonObject toJson() {
        QJsonObject jsonObj;
        jsonObj.insert("name", name);
        jsonObj.insert("price", price);
        jsonObj.insert("description", description);
        jsonObj.insert("img_path", img_path);

        QJsonArray arr = {};
        for (auto qstr : labels) {
            arr.append(QJsonValue(qstr));
        }

        jsonObj.insert("labels", arr);
        return jsonObj;
    }

    friend bool operator==(const Dish & d1, const Dish & d2) {
        return d1.name == d2.name;
    }

    friend bool operator==(const Dish & d1, const QString& name) {
        return d1.name == name;
    }
};
