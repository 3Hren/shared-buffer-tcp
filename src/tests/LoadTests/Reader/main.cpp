#include <QCoreApplication>
#include "Reader.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Reader reader;
    reader.run();
    
    return a.exec();
}
