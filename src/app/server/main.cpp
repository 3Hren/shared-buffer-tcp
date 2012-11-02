#include <QCoreApplication>

#include <BufferServer.h>

#include <QTextStream>
#include <QDebug>

using namespace BufferStorage;

void showHelp(char *argv[]) {
    QTextStream out(stderr);
    out << QString("Usage:").leftJustified(16, ' ') << QString("%1 START_ADDRESS BUFFER_COUNT BUFFER_MAXIMUM_SIZE\n").arg(argv[0]);
    out << QString("Exapmle:").leftJustified(16, ' ') << QString("%1 1000 300 1024\n").arg(argv[0]);
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

