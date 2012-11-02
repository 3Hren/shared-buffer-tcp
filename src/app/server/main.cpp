#include <QCoreApplication>

#include <BufferServer.h>

#include <QDebug>

using namespace BufferStorage;

void showHelp(char *argv[]) {
    qCritical() << QString("Usage:").leftJustified(16, ' ').toUtf8().constData() << QString("%1 START_ADDRESS BUFFER_COUNT BUFFER_MAXIMUM_SIZE\n").arg(argv[0]).toUtf8().constData();
    qCritical() << QString("Exapmle:").leftJustified(16, ' ').toUtf8().constData() << QString("%1 1000 300 1024\n").arg(argv[0]).toUtf8().constData();
    exit(-1);
}

int main(int argc, char *argv[])
{    
    if (argc < 4)
        showHelp(argv);

    bool isEverythingOk = true;
    bool ok = false;
    int startAddress = QString(argv[1]).toInt(&ok);
    isEverythingOk &= ok;
    int count = QString(argv[2]).toInt(&ok);
    isEverythingOk &= ok;
    int maximumSize = QString(argv[3]).toInt(&ok);
    isEverythingOk &= ok;
    if (!isEverythingOk)
        showHelp(argv);

    qDebug() << QString("BufferServer started at localhost:14690. Start address: %1. Buffer count: %2. All buffers has %3 maximum size.")
                .arg(startAddress)
                .arg(count)
                .arg(maximumSize).toUtf8().constData();

    QCoreApplication a(argc, argv);
    BufferServer server;
    BufferInfoMap map;
    for (int i = 0; i < count; ++i)
        map.insert(startAddress + 2 * i, maximumSize);

    server.initializeBuffers(map);
    server.run();
    
    return a.exec();
}

