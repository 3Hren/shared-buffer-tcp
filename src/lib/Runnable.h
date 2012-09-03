#pragma once

#include <QObject>

class Runnable : public QObject {
    Q_OBJECT
public:
    Runnable(QObject *parent = 0) : QObject(parent) {}
    virtual void run() = 0;
};
