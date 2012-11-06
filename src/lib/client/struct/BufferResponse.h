#pragma once

#include "AbstractResponse.h"

#include "SignalValue.h"

namespace BufferStorage {
struct BufferResponse : public AbstractResponse {
    BufferResponse() :
        AbstractResponse(),
        bufferId(-1)
    {}

    BufferResponse(ProtocolType requestType, BufferId bufferId, const TimeStampVector &timeStamps, const SignalValueVector &signalDatas) :
        AbstractResponse(requestType),
        bufferId(bufferId),
        timeStamps(timeStamps),
        signalDatas(signalDatas)
    {}

    BufferId bufferId;
    TimeStampVector timeStamps;
    SignalValueVector signalDatas;
};
}
