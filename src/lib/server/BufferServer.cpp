#include "BufferServer.h"

#include "ServerConnectionHandler.h"

#include "buffer/HashTableBufferManager.h"

#include "exceptions/ServerException.h"

#include <QTcpServer>
#include <QTcpSocket>

using namespace BufferStorage;

BufferServer::BufferServer(QObject *parent) :
    Runnable(parent),
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

void BufferServer::run(const QString &host, quint16 port)
{
    if (!server->listen(QHostAddress(host), port))
        throw ServerCouldNotStartException(host, port);
}

void BufferServer::run(const QString &host)
{
    run(host, getStandardPort());
}

void BufferServer::run()
{
    run(QHostAddress(QHostAddress::LocalHost).toString());
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

void BufferServer::initializeBuffers(const BufferInfoTable &bufferInfoTable)
{    
    bufferManager->setBuffers(bufferInfoTable);
}

BufferManager *BufferServer::getBufferManager() const
{
    return bufferManager;
}

//! После выполнения этого метода сервер отвечает за удаление BufferManager'а.
void BufferServer::setBufferManager(BufferManager *bufferManager)
{
    delete this->bufferManager;
    this->bufferManager = bufferManager;
}

void BufferServer::acceptConnection()
{
    QTcpSocket *socket = server->nextPendingConnection();     
    ConnectionHandler *requestHandler = new ServerConnectionHandler(socket, this);
    qDebug() << QString("New connection from: %1:%2").arg(socket->peerAddress().toString()).arg(socket->peerPort());
    Q_UNUSED(requestHandler);
}
