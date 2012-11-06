#pragma once

#include "Response.h"
#include "SignalData.h"

namespace BufferStorage {
struct BufferResponse : public Response {
    BufferResponse() :
        Response(),
        id(-1)
    {}

    BufferResponse(ProtocolType requestType, quint16 id, const QVector<TimeStamp> &timeStamps, const QVector<SignalData> &signalDatas) :
        Response(requestType),
        id(id),
        timeStamps(timeStamps),
        signalDatas(signalDatas)
    {}

    quint16 id; //! @todo: make type safe
    QVector<TimeStamp> timeStamps;
    QVector<SignalData> signalDatas;
};
}
