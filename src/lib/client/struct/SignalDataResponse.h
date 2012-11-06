#pragma once

#include "AbstractResponse.h"

#include "SignalValue.h"

namespace BufferStorage {
struct SignalDataResponse : public AbstractResponse
{
    SignalDataResponse() : AbstractResponse() {}
    SignalDataResponse(ProtocolType requestType, TimeStamp timeStamp, const SignalValueVector &signalDatas) :
        AbstractResponse(requestType),
        timeStamp(timeStamp),
        signalDatas(signalDatas)
    {}

    TimeStamp timeStamp;
    SignalValueVector signalDatas;//! @todo: rename
};
}
