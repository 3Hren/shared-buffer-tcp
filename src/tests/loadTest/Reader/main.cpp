#include <QCoreApplication>
#include "ThreadReader.h"

static const int THREAD_COUNT = 300;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QList<ThreadReader *> readers;
    for (int i = 0; i < THREAD_COUNT; ++i)
        readers.append(new ThreadReader);

    foreach (ThreadReader *reader, readers)
        reader->start();
    
    return a.exec();
}
