#include "Server.h"

#include "../exceptions/ServerCouldNotStartException.h"
#include "buffer/HashTableBufferManager.h"
#include "../ConnectionHandler.h"
#include "ServerConnectionHandler.h"

#include <QTcpServer>

Server::Server(QObject *parent) :
    Runnable(parent),
    server(new QTcpServer(this)),
    bufferManager(new HashTableBufferManager)
{
    connect(server,SIGNAL(newConnection()),SLOT(acceptConnection()));
}

Server::~Server()
{
    delete bufferManager;
}

quint16 Server::getStandardPort()
{
    return static_cast<quint16>(14690);
}

void Server::run(const QString &host, quint16 port)
{
    if (!server->listen(QHostAddress(host), port))
        throw ServerCouldNotStartException(host, port);
}

void Server::run(const QString &host)
{
    run(host, getStandardPort());
}

void Server::run()
{
    run(QHostAddress(QHostAddress::LocalHost).toString());
}

bool Server::isListening() const
{
    return server->isListening();
}

QString Server::getHost() const
{
    return server->serverAddress().toString();
}

quint16 Server::getPort() const
{
    return server->serverPort();
}

void Server::initializeBuffers(const BufferInfoMap &bufferInfoMap)
{    
    bufferManager->setBuffers(bufferInfoMap);
}

BufferManager *Server::getBufferManager() const
{
    return bufferManager;
}

void Server::acceptConnection()
{
    QTcpSocket *socket = server->nextPendingConnection();     
    ConnectionHandler *requestHandler = new ServerConnectionHandler(socket, this);
    Q_UNUSED(requestHandler);
}
