#include "Model.h"

#include <BufferClient.h>

#include <QTimer>
#include <QDateTime>

#include <QDebug>

Model::Model(quint16 startAddress, quint16 buffersCount, QObject *parent) :
    QAbstractTableModel(parent),
    client(new BufferClient(this)),
    startAddress(startAddress),
    buffersCount(buffersCount)
{
    if (!client->blockingConnectToServer())
        qFatal("Cannot connect to server");

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
    const SignalBuffer &signalBuffer= client->blockingGetBuffer(startAddress);
    timeStamps = signalBuffer.timeStampVector;

    signalDatas.clear();
    for (quint16 address = startAddress; address < startAddress + 2 * buffersCount; address += 2) {
        const SignalBuffer &signalBuffer = client->blockingGetBuffer(address);
        signalDatas.append(signalBuffer.signalValueVector);
    }
    endResetModel();
}
