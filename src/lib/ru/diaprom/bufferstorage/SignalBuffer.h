#pragma once

#include "SignalValue.h"

namespace BufferStorage {
struct SignalBuffer {
    SignalBuffer() {}
    SignalBuffer(const TimeStampVector &timeStampVector, const SignalValueVector &signalValueVector) : timeStampVector(timeStampVector), signalValueVector(signalValueVector) {}

    TimeStampVector timeStampVector;
    SignalValueVector signalValueVector;

    inline bool operator ==(const SignalBuffer &other) const {
        return timeStampVector == other.timeStampVector && signalValueVector == other.signalValueVector;
    }
};

inline QDataStream &operator <<(QDataStream &out, const SignalBuffer &signalBuffer) {
    out << signalBuffer.timeStampVector << signalBuffer.signalValueVector;
    return out;
}

inline QDataStream &operator >>(QDataStream &in, SignalBuffer &signalBuffer) {
    in >> signalBuffer.timeStampVector >> signalBuffer.signalValueVector;
    return in;
}
}
