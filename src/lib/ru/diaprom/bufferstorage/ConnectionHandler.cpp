#include "ConnectionHandler.h"

#include "BufferStorageGlobal.h"
#include "protocol/ProtocolMessage.h"
#include "protocol/Request.h"
#include "protocol/ProtocolMessageFactory.h"

#include <QTcpSocket>
#include <QSharedPointer>

using namespace BufferStorage;

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

    //! @note: Don't read message until its completely delivered
    if (socket->bytesAvailable() < requestSize)
        return;    

    Magic magic;
    in >> magic;
    if (magic != MAGIC) {
        socket->disconnectFromHost();
        return;
    }

    ProtocolType type = UNKNOWN_PROTOCOL_TYPE;
    in >> type;

    ProtocolMessageFactory protocolFactory;
    QSharedPointer<ProtocolMessage> protocolMessage(protocolFactory.createProtocolMessage(type));
    protocolMessage->decode(&in);
    processProtocolMessage(protocolMessage);

    requestSize = 0;
}
