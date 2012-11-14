#include "Model.h"

#include <ru/diaprom/bufferstorage/BufferClientImplementation.h>
#include <ru/diaprom/bufferstorage/exceptions/BufferStorageException.h>

#include <QTimer>
#include <QDateTime>

#include <QDebug>

Model::Model(quint16 startAddress, quint16 buffersCount, QObject *parent) :
    QAbstractTableModel(parent),
    client(new BufferClientImplementation(this)),
    startAddress(startAddress),
    buffersCount(buffersCount)
{
    if (!client->blockingConnectToServer())
        qFatal("Cannot connect to server");

    for (quint16 address = startAddress; address < startAddress + 2 * buffersCount; address += 2) {
        SignalValueVector signalValues;
        for (int i = 0; i < buffersCount; ++i)
            signalValues.append(SignalValue());

        signalDatas.append(signalValues);
    }

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(updateValues()));
    timer->start(1000);
}

int Model::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return timeStamps.size();
}

int Model::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return 1 + buffersCount;
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        if (section == 0) {
            return "Time";
        } else {
            return startAddress + 2 * (section - 1);
        }
    } else if (orientation == Qt::Vertical) {
        return section + 1;
    }

    return QVariant();
}

QVariant Model::data(const QModelIndex &index, int role) const
{
    int row(index.row());
    int column(index.column());
    if (!index.isValid() || row < 0 || row >= rowCount(index.parent()) || column < 0 || column >= columnCount(index.parent()))
        return QVariant();

    if (role == Qt::DisplayRole) {
        if (column == 0) {
            return QDateTime::fromTime_t(timeStamps.at(row)).toString("hh:mm:ss");
        } else {
            QString value = QString::number(signalDatas.at(column - 1).at(row).value, 'f', 3);
            return value;
        }
    }

    return QVariant();
}

void Model::updateValues()
{
    beginResetModel();
    QTime timer;
    timer.start();
    try {
        const SignalBuffer &signalBuffer= client->blockingGetBuffer(startAddress);
        timeStamps = signalBuffer.timeStampVector;

        for (quint16 address = startAddress; address < startAddress + 2 * buffersCount; address += 2) {
            const SignalBuffer &signalBuffer = client->blockingGetBuffer(address);
            int index = (address - startAddress) / 2;
            signalDatas.replace(index, signalBuffer.signalValueVector);
        }
    } catch (BufferStorageException &exception) {
        qCritical() << exception.getReason();
    }
    qDebug() << QString("'SELECT *' was done in %1 msecs").arg(timer.elapsed());

    endResetModel();
}
