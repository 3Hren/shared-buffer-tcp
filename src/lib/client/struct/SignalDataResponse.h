#pragma once

#include "Response.h"

#include "SignalData.h"

namespace BufferStorage {
struct SignalDataResponse : public Response
{
    SignalDataResponse() : Response() {}
    SignalDataResponse(ProtocolType requestType, TimeStamp timeStamp, const QVector<SignalData> &signalDatas) :
        Response(requestType),
        timeStamp(timeStamp),
        signalDatas(signalDatas)
    {}

    TimeStamp timeStamp;
    QVector<SignalData> signalDatas;
};
}
