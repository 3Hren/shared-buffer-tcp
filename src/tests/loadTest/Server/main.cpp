#include <QCoreApplication>

#include <BufferServer.h>

#include <QTextStream>
#include <QDebug>

using namespace BufferStorage;
int main(int argc, char *argv[])
{
    QTextStream out(stderr);
    if (argc < 4) {
        out << QString("Usage:\t\t%1 START_ADDRESS BUFFER_COUNT BUFFER_MAXIMUM_SIZE\n"
                       "Exapmle:\t\t%1 1000 300 1024\n").arg(argv[0]);
        return 0;
    }

    bool ok = false;
    int startAddress = QString(argv[1]).toInt(&ok);
    if (!ok)
        return -1;

    int count = QString(argv[2]).toInt(&ok);
    if (!ok)
        return -2;

    int maximumSize = QString(argv[3]).toInt(&ok);
    if (!ok)
        return -3;

    qDebug() << QString("BufferServer started at localhost:14690. Start address: %1. Buffer count: %2. All buffers has %3 maximum size.")
                .arg(startAddress)
                .arg(count)
                .arg(maximumSize);

    QCoreApplication a(argc, argv);
    BufferServer server;
    BufferInfoMap map;
    for (int i = 0; i < count; ++i)
        map.insert(startAddress + 2 * i, maximumSize);

    server.initializeBuffers(map);
    server.run();
    
    return a.exec();
}

