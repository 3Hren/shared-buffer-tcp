#pragma once

#include "Response.h"
#include "SignalData.h"

namespace BufferStorage {
struct BufferResponse : public Response {
    BufferResponse() :
        Response(),
        bufferId(-1)
    {}

    BufferResponse(ProtocolType requestType, BufferId bufferId, const QVector<TimeStamp> &timeStamps, const QVector<SignalData> &signalDatas) :
        Response(requestType),
        bufferId(bufferId),
        timeStamps(timeStamps),
        signalDatas(signalDatas)
    {}

    BufferId bufferId;
    QVector<TimeStamp> timeStamps;
    QVector<SignalData> signalDatas;
};
}
