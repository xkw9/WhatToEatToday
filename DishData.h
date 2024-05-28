#ifndef DISHDATA_H
#define DISHDATA_H

#endif // DISHDATA_H

#include "Dish.h"
#include <vector>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDir>
#include <QDebug>
class DishData {
    vector<Dish> dishes = {};
public:
    DishData() {
        LoadDishData();
    }

    void LoadDishData() {
        QString path = QDir::currentPath();
        QFile file(path + "//Resources//DishData.json");
        if (not file.exists()) {
            qDebug() << "Dish Data Files not exist";
            return;
        }
        if (not file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Cant open Dish Data Files when Loading";
            return;
        }
        QJsonParseError jsonErr;
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &jsonErr);
        file.close();
        if (doc.isNull()) {
            qDebug() << "Dish Data Files is null";
            return;
        }
        if (jsonErr.error != QJsonParseError::NoError) {
            qDebug() << "Error when reading the Dish Data";
            return;
        }
        if (not doc.isArray()) {
            qDebug() << "Dish Data JsonFiles has wrong Format";
            return;
        }
        QJsonArray arr = doc.array();

        for (auto d : arr) {
            if (d.isObject()) {
                QJsonObject jsonObj = d.toObject();
                dishes.push_back(Dish(jsonObj));
            } else {
                qDebug() << "Dish Data JsonFiles has wrong Format";
                return;
            }
        }

        qDebug() << "Data Load Compelete";
    }

    void SaveDishData() {
        QJsonArray arr = {};
        for (auto d : dishes) {
            arr.append(d.toJson());
        }

        QJsonDocument doc(arr);
        QString path = QDir::currentPath();
        QFile file(path + "//Resources//DishData.json");
        if (not file.exists()) {
            qDebug() << "Dish Data Files not exist";
            return;
        }

        if (not file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "Cant open Dish Data Files when Saving";
            return;
        }
        file.write(doc.toJson());
        file.close();

        qDebug() << "Data Save Compelete";
    }

    void AddDish(Dish d) {
        dishes.push_back(d);
    }

};
