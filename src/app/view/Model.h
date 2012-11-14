#pragma once

#include <QAbstractTableModel>

#include <BufferClientImplementation.h>

#include <QList>
#include <QVector>

using namespace BufferStorage;

class Model : public QAbstractTableModel
{
    Q_OBJECT
    BufferClientImplementation *client;
    TimeStampVector timeStamps;
    QList<SignalValueVector> signalDatas;

    quint16 startAddress;
    quint16 buffersCount;
public:
    Model(quint16 startAddress, quint16 buffersCount, QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

private slots:
    void updateValues();
};
