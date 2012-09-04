#include <QCoreApplication>
#include "Writer.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);   
    Writer writer;
    writer.run();
    
    return a.exec();
}
