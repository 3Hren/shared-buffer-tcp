#include <QCoreApplication>

#include "ThreadedWriter.h"

#include <QStringList>

void showHelp(char *argv[]) {
    qCritical() << QString("Usage:").leftJustified(16, ' ').toUtf8().constData() << QString("%1 THREAD_COUNT TIMEOUT BUFFER_COUNT").arg(argv[0]).toUtf8().constData();
    qCritical() << QString("Exapmle:").leftJustified(16, ' ').toUtf8().constData() << QString("%1 1 9 64\n").arg(argv[0]).toUtf8().constData();
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
    const int bufferCount = QString(argv[3]).toInt(&ok);
    isEverythingOk &= ok;
    if (!isEverythingOk)
        showHelp(argv);

    qDebug() << QString("%1 ThreadedWriter(s) started.\nTimeout: %2\nStart address: 0\nBuffer count: %3")
                .arg(threadCount)
                .arg(timeout)
                .arg(bufferCount).toUtf8().constData();

    QList<ThreadedWriter *> writers;
    for (int i = 0; i < threadCount; ++i)
        writers.append(new ThreadedWriter(timeout, bufferCount));

    foreach (ThreadedWriter *writer, writers)
        writer->start();
    
    return a.exec();
}
