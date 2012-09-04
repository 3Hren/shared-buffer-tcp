#include <QCoreApplication>

#include <server/Server.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Server server;
    BufferInfoMap map;
    for (int i = 0; i < 300; ++i) {
        map.insert(i, 1024);
    }
    server.initializeBuffers(map);
    server.run();
    
    return a.exec();
}
