#pragma once

#include <QtAlgorithms>
#include <QDataStream>

#include <QDebug>

namespace BufferServer {
struct SignalData {
    SignalData() :
        value(0.0),
        errorCode(0)
    {}

    SignalData(float value, quint16 errorCode) :
        value(value),
        errorCode(errorCode)
    {}

    float value;
    quint16 errorCode;

    bool operator==(const SignalData &other) const {
        return qFuzzyCompare(value, other.value) && errorCode == other.errorCode;
    }
};

inline QDataStream &operator <<(QDataStream &out, const SignalData &signalData) {
    out << signalData.value << signalData.errorCode;
    return out;
}

inline QDataStream &operator >>(QDataStream &in, SignalData &signalData) {
    in >> signalData.value >> signalData.errorCode;
    return in;
}

inline QDebug operator <<(QDebug debug, const SignalData &signalData) {
    debug.nospace() << QString("SignalData(%1, %2)").arg(signalData.value).arg(signalData.errorCode);
    return debug.space();
}
}
