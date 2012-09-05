#pragma once

#include <QObject>

#include "Global.h"

class QTcpSocket;
class RequestProtocol;
class ConnectionHandler : public QObject
{
    Q_OBJECT

protected:
    QTcpSocket *socket;
    MessageSize requestSize;

public:
    ConnectionHandler(QTcpSocket *socket, QObject *parent = 0);

protected:
    virtual void processRequest(RequestProtocol *requestProtocol) = 0;

public Q_SLOTS:
    void readPendingData();
};
