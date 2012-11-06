#pragma once

#include "BufferStorageGlobal.h"

namespace BufferStorage {
struct SignalValue
{
    SignalValue() : value(0.0), errorCode(0) {}
    SignalValue(float value, ErrorCode errorCode) : value(value), errorCode(errorCode) {}

    float value;
    ErrorCode errorCode;

    inline bool operator ==(const SignalValue &other) const {
        return qFuzzyCompare(value, other.value) && errorCode == other.errorCode;
    }
};

#include <QDataStream>
inline QDataStream &operator <<(QDataStream &out, const SignalValue &signalValue) {
    out << signalValue.value << signalValue.errorCode;
    return out;
}

inline QDataStream &operator >>(QDataStream &in, SignalValue &signalValue) {
    in >> signalValue.value >> signalValue.errorCode;
    return in;
}

inline QDebug operator <<(QDebug debug, const SignalValue &signalValue) {
    debug.nospace() << QString("SignalValue(%1, %2)").arg(signalValue.value).arg(signalValue.errorCode);
    return debug.space();
}

#include <QVector>
typedef QVector<SignalValue> SignalValueVector;
}
