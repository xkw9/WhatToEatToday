#ifndef DISHDATA_H
#define DISHDATA_H

#endif // DISHDATA_H

#include <QDebug>
#include <QCoreApplication>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include "Config.h"
#include "utils.h"
#include <algorithm>
#include <vector>

const QString DISH_DATA_PATH = "/Resources/DishData.json";

class DishData
{
public:
    QList<Dish> dishes = {};

    DishData() { LoadDishData(); }

    void LoadDishData()
    {
        QString path = QCoreApplication::applicationDirPath();

        QFile file(path + DISH_DATA_PATH);
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

        dishes.clear();
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

    void SaveDishData()
    {
        QJsonArray arr = {};
        for (auto d : dishes) {
            arr.append(d.toJson());
        }

        QJsonDocument doc(arr);
        QString path = QCoreApplication::applicationDirPath();
        QFile file(path + DISH_DATA_PATH);
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

    void AddDish(Dish d)
    {
        // 防止重复
        if (dishes.contains(d)) {
            return;
        }

        dishes.push_back(d);
        SaveDishData();
    }

    void RemoveDish(QString name)
    {
        Dish d;
        d.name = name;
        dishes.removeAll(d);
        SaveDishData();
    }

    void RemoveDish(int index)
    {
        if (index < 0 or index >= dishes.size()) {
            return;
        }
        dishes.removeAt(index);
        SaveDishData();
    }
};
