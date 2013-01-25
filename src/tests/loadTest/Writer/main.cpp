#include <QCoreApplication>

#include "ThreadedWriter.h"

#include <QStringList>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    bool ok = false;
    const int threadCount = QString(argv[1]).toInt(&ok);
    Q_ASSERT_X(ok, Q_FUNC_INFO, "threadCount");
    const int timeout = QString(argv[2]).toInt(&ok);
    Q_ASSERT_X(ok, Q_FUNC_INFO, "timeout");
    const int bufferCount = QString(argv[3]).toInt(&ok);
    Q_ASSERT_X(ok, Q_FUNC_INFO, "bufferCount");


    QList<ThreadedWriter *> writers;
    for (int i = 0; i < threadCount; ++i)
        writers.append(new ThreadedWriter(timeout, bufferCount));

    foreach (ThreadedWriter *writer, writers)
        writer->start();
    
    return a.exec();
}
