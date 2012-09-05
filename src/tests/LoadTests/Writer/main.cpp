#include <QCoreApplication>

#include "ThreadedWriter.h"

static const int WRITER_THREAD_COUNT = 5;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);   
    QList<ThreadedWriter *> writers;
    for (int i = 0; i < WRITER_THREAD_COUNT; ++i)
        writers.append(new ThreadedWriter);

    foreach (ThreadedWriter *writer, writers)
        writer->start();
    
    return a.exec();
}
