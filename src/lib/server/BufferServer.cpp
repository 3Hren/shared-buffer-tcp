#include "BufferServer.h"

#include "ServerConnectionHandler.h"

#include "buffer/HashTableBufferManager.h"

#include "exceptions/ServerException.h"

#include <QTcpServer>
#include <QTcpSocket>

using namespace BufferStorage;

BufferServer::BufferServer(QObject *parent) :
    QObject(parent),
    server(new QTcpServer(this)),
    bufferManager(new HashTableBufferManager)
{
    connect(server, SIGNAL(newConnection()), SLOT(acceptConnection()));
}

BufferServer::~BufferServer()
{
    delete bufferManager;
}

quint16 BufferServer::getStandardPort()
{
    return static_cast<quint16>(14690);
}

bool BufferServer::isListening() const
{
    return server->isListening();
}

QString BufferServer::getHost() const
{
    return server->serverAddress().toString();
}

quint16 BufferServer::getPort() const
{
    return server->serverPort();
}

void BufferServer::initBuffers(const BufferInfoTable &bufferInfoTable)
{    
    bufferManager->initBuffers(bufferInfoTable);
}

void BufferServer::initBuffers(BufferId count, BufferSize maxSize, BufferId startId, BufferId offset)
{
    bufferManager->initBuffers(count, maxSize, startId, offset);
}

void BufferServer::run(const QString &host, quint16 port)
{
    if (!server->listen(QHostAddress(host), port))
        throw ServerException(QString("Server could not start at '%1:%2': %3").arg(host).arg(port).arg(server->errorString()));
}


BufferManager *BufferServer::getBufferManager() const
{
    return bufferManager;
}

//! Сервер отвечает за удаление BufferManager'а.
void BufferServer::setBufferManager(BufferManager *bufferManager)
{
    delete this->bufferManager;
    this->bufferManager = bufferManager;
}

void BufferServer::acceptConnection()
{
    QTcpSocket *socket = server->nextPendingConnection();     
    ConnectionHandler *requestHandler = new ServerConnectionHandler(socket, this);
    qDebug() << QString("New connection from: '%1:%2'").arg(socket->peerAddress().toString()).arg(socket->peerPort());
    Q_UNUSED(requestHandler);
}
