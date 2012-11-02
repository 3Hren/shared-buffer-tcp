#include <QApplication>

#include "Model.h"
#include "View.h"

#include <QDebug>

void showHelp(char *argv[]) {
    qCritical() << QString("Usage:").leftJustified(16, ' ').toUtf8().constData() << QString("%1 START_ADDRESS BUFFER_COUNT").arg(argv[0]).toUtf8().constData();
    qCritical() << QString("Exapmle:").leftJustified(16, ' ').toUtf8().constData() << QString("%1 1000 300").arg(argv[0]).toUtf8().constData();
    exit(-1);
}

int main(int argc, char *argv[])
{    
    QApplication a(argc, argv);
    if (argc < 3)
        showHelp(argv);

    bool isEverythingOk = true;
    bool ok = false;
    quint16 startAddress = QString(argv[1]).toUInt(&ok);
    isEverythingOk &= ok;
    quint16 buffersCount = QString(argv[2]).toUInt(&ok);
    isEverythingOk &= ok;
    if (!isEverythingOk)
        showHelp(argv);

    Model model(startAddress, buffersCount);
    View v;
    v.setModel(&model);
    v.show();

    return a.exec();
}
