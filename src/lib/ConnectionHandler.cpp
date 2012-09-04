#include "ConnectionHandler.h"

#include "Global.h"
#include "protocol/RequestProtocol.h"
#include "protocol/RequestProtocolFactory.h"

#include <QTcpSocket>

ConnectionHandler::ConnectionHandler(QTcpSocket *socket, QObject *parent) :
    QObject(parent),
    socket(socket),
    requestSize(0)
{        
    connect(socket,SIGNAL(readyRead()),SLOT(readPendingData()));
}

void ConnectionHandler::readPendingData()
{    
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_4_8);
    in.setFloatingPointPrecision(QDataStream::SinglePrecision);

    if (requestSize == 0) {
        if (socket->bytesAvailable() < (int)sizeof(MessageSize))
            return;
        in >> requestSize;
    }

    // Don't read message until its completely delivered
    if (socket->bytesAvailable() < requestSize)
        return;    

    Magic magic;
    in >> magic;
    if (magic != MAGIC) {
        socket->disconnectFromHost();
        return;
    }

    RequestProtocolFactory protocolFactory;
    QScopedPointer<RequestProtocol> inputRequest(protocolFactory.createRequestProtocol(&in));    
    processRequest(inputRequest.data());

    requestSize = 0;
}
