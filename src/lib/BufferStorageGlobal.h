#pragma once

#include <QAbstractSocket>
#include <QMap>
#include <QHash>

#include <QDataStream>
#define DECLARE_SERIALIZATION_FOR_ENUM(Type) \
    inline QDataStream &operator <<(QDataStream &out, const Type &t) { \
        out << static_cast<quint8>(t); \
        return out; \
    } \
    inline QDataStream &operator >>(QDataStream &in, Type &t) { \
        quint8 n = 0; \
        in >> n; \
        t = static_cast<Type>(n); \
        return in; \
    }

namespace BufferStorage {
typedef quint32 MessageSize;
typedef quint32 Magic;
static const Magic MAGIC = 927932743;
enum ProtocolType {
    REQUEST_PUSH = 0,
    REQUEST_GET_SIGNAL_DATA,
    REQUEST_GET_BUFFER,

    RESPONSE_PUSH = 100 + 0,
    RESPONSE_GET_SIGNAL_DATA = 100 + 1,
    RESPONSE_GET_BUFFER = 100 + 2,
    RESPONSE_ERROR = 100 + 3,

    UNKNOWN = 255
};
DECLARE_SERIALIZATION_FOR_ENUM(ProtocolType)

namespace ProtocolError {
enum Type {
    NORMAL = 0,

    WRONG_REQUEST_TYPE = 100,
    WRONG_BUFFER_ID = 110,
    WRONG_INPUT_ARRAY_SIZE = 111,
    WRONG_TIME_STAMP = 112,

    UNKNOWN = 255
};
}

struct SocketError {
    SocketError() : error(QAbstractSocket::UnknownSocketError) {}
    QAbstractSocket::SocketError error;
    QString errorString;
};

typedef QMap<quint16, quint16> BufferInfoMap;
typedef quint32 TimeStamp;
}
