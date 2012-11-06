#pragma once

#include "AbstractResponse.h"

#include "SignalData.h"

namespace BufferStorage {
struct BufferResponse : public AbstractResponse {
    BufferResponse() :
        AbstractResponse(),
        bufferId(-1)
    {}

    BufferResponse(ProtocolType requestType, BufferId bufferId, const QVector<TimeStamp> &timeStamps, const QVector<SignalData> &signalDatas) :
        AbstractResponse(requestType),
        bufferId(bufferId),
        timeStamps(timeStamps),
        signalDatas(signalDatas)
    {}

    BufferId bufferId;
    QVector<TimeStamp> timeStamps;
    QVector<SignalData> signalDatas;
};
}
