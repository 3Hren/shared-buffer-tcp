#include <QCoreApplication>

#include <Server.h>

static const int BUFFER_MAXIMUM_SIZE = 1024;
static const int BUFFER_COUNT = 300;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Server server;
    BufferInfoMap map;
    for (int i = 0; i < BUFFER_COUNT; ++i)
        map.insert(i, BUFFER_MAXIMUM_SIZE);

    server.initializeBuffers(map);
    server.run();
    
    return a.exec();
}

