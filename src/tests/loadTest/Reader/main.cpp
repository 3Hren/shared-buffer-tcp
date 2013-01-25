#include <QCoreApplication>
#include "ThreadReader.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    bool ok = false;
    const int threadCount = QString(argv[1]).toInt(&ok);
    Q_ASSERT_X(ok, Q_FUNC_INFO, "threadCount");
    const int timeout = QString(argv[2]).toInt(&ok);
    Q_ASSERT_X(ok, Q_FUNC_INFO, "timeout");
    const BufferId startAddress = QString(argv[3]).toUInt(&ok);
    Q_ASSERT_X(ok, Q_FUNC_INFO, "startAddress");
    const BufferId bufferCount = QString(argv[4]).toUInt(&ok);
    Q_ASSERT_X(ok, Q_FUNC_INFO, "bufferCount");

    QList<ThreadReader *> readers;
    for (int i = 0; i < threadCount; ++i)
        readers.append(new ThreadReader(timeout, startAddress, bufferCount));

    foreach (ThreadReader *reader, readers)
        reader->start();
    
    return a.exec();
}
