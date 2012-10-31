#pragma once

#include <QAbstractSocket>
#include <QMap>
#include <QHash>

namespace BufferStorage {
static const quint32 MAGIC = 9275623;

namespace ProtocolType {
enum Type {
    PushRequest = 0,
    GetSignalDataRequest = 1,
    GetSignalDataResponse = 2,
    GetBufferRequest = 3,
    GetBufferResponse = 4,

    ErrorMessageResponse = 10,

    SocketError = 200,

    UnknownType = 255
};
}

namespace ProtocolError {
enum Type {
    WrongRequestType = 100,

    BufferNotFound = 110,
    WrongInputArraySize = 111,
    WrongTimeStamp = 112,

    NoError = 254,
    UnknownError = 255
};
}

struct SocketError {
    SocketError() : error(QAbstractSocket::UnknownSocketError) {}
    QAbstractSocket::SocketError error;
    QString errorString;
};

typedef QMap<quint16, quint16> BufferInfoMap;
typedef quint32 MessageSize;
typedef quint32 Magic;
typedef quint32 TimeStamp;
}
