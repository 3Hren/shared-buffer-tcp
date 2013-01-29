#include <QCoreApplication>
#include "ThreadReader.h"

void showHelp(char *argv[]) {
    qCritical() << QString("Usage:").leftJustified(16, ' ').toUtf8().constData() << QString("%1 THREAD_COUNT TIMEOUT START_ADDRESS BUFFER_COUNT").arg(argv[0]).toUtf8().constData();
    qCritical() << QString("Exapmle:").leftJustified(16, ' ').toUtf8().constData() << QString("%1 1 9 0 64\n").arg(argv[0]).toUtf8().constData();
    exit(-1);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    bool isEverythingOk = true;
    bool ok = true;
    const int threadCount = QString(argv[1]).toInt(&ok);
    isEverythingOk &= ok;
    const int timeout = QString(argv[2]).toInt(&ok);
    isEverythingOk &= ok;
    const BufferId startAddress = QString(argv[3]).toUInt(&ok);
    isEverythingOk &= ok;
    const BufferId bufferCount = QString(argv[4]).toUInt(&ok);
    isEverythingOk &= ok;
    if (!isEverythingOk)
        showHelp(argv);

    qDebug() << QString("%1 ThreadReader(s) started.\nTimeout: %2\nStart address: %3\nBuffer count: %4")
                .arg(threadCount)
                .arg(timeout)
                .arg(startAddress)
                .arg(bufferCount).toUtf8().constData();

    QList<ThreadReader *> readers;
    for (int i = 0; i < threadCount; ++i)
        readers.append(new ThreadReader(timeout, startAddress, bufferCount));

    foreach (ThreadReader *reader, readers)
        reader->start();
    
    return a.exec();
}
