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

namespace Utils {
static QHash<QString, int> registeredMetaTypes = QHash<QString, int>();
//! Metatype auto-registrator
template<typename T>
class MetaTypeRegistrator {
public:
    MetaTypeRegistrator(const QString &typeName) {
        if (!registeredMetaTypes.contains(typeName)) {
            int metaTypeId = qRegisterMetaType<T>(typeName.toUtf8());
            registeredMetaTypes.insert(typeName, metaTypeId);
        }
    }
};
}

#define Q_BS_REGISTER_METATYPE(Class) \
    Q_DECLARE_METATYPE(Class) \
    static Utils::MetaTypeRegistrator<Class> Class##Registrator(#Class);

namespace BufferStorage {
typedef quint32 MessageSize;
typedef quint32 Magic;
typedef quint16 BufferId;
typedef quint16 BufferSize;
typedef quint16 ErrorCode;
typedef QMap<BufferId, BufferSize> BufferInfoTable;
typedef QMapIterator<BufferId, BufferSize> BufferInfoTableIterator;
typedef quint32 TimeStamp;
typedef QVector<TimeStamp> TimeStampVector;

static const Magic MAGIC = 927932743;
enum ProtocolType {
    REQUEST_PUSH = 0,
    REQUEST_GET_SIGNAL_VALUES = 1,
    REQUEST_GET_BUFFER = 2,

    RESPONSE_PUSH = 100 + 0,
    RESPONSE_GET_SIGNAL_VALUES = 100 + 1,
    RESPONSE_GET_BUFFER = 100 + 2,
    RESPONSE_ERROR = 100 + 3,

    UNKNOWN_PROTOCOL_TYPE = 255
};
DECLARE_SERIALIZATION_FOR_ENUM(ProtocolType)

enum ErrorType {
    NORMAL = 0,
    WRONG_REQUEST_TYPE = 100,
    WRONG_BUFFER_ID = 110,
    WRONG_INPUT_ARRAY_SIZE = 111,
    WRONG_TIME_STAMP = 112,
    SOCKET_ERROR = 200,

    UNKNOWN_ERROR_TYPE = 255
};
DECLARE_SERIALIZATION_FOR_ENUM(ErrorType)
}
