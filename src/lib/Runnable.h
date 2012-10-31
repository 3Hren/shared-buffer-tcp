#pragma once

#include <QObject>
namespace BufferServer {
class Runnable : public QObject {
    Q_OBJECT
public:
    Runnable(QObject *parent = 0) : QObject(parent) {}
    virtual void run() = 0;
};
}
