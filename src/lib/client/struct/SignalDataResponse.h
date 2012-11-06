#pragma once

#include "AbstractResponse.h"

#include "SignalData.h"

namespace BufferStorage {
struct SignalDataResponse : public AbstractResponse
{
    SignalDataResponse() : AbstractResponse() {}
    SignalDataResponse(ProtocolType requestType, TimeStamp timeStamp, const QVector<SignalData> &signalDatas) :
        AbstractResponse(requestType),
        timeStamp(timeStamp),
        signalDatas(signalDatas)
    {}

    TimeStamp timeStamp;
    QVector<SignalData> signalDatas;
};
}
