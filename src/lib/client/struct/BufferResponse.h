#pragma once

#include "Response.h"
#include "SignalData.h"

namespace BufferServer {
struct BufferResponse : public Response {
    BufferResponse() :
        Response(),
        id(-1)
    {}

    BufferResponse(quint8 requestType, quint16 id, const QVector<TimeStamp> &timeStamps, const QVector<SignalData> &signalDatas) :
        Response(requestType),
        id(id),
        timeStamps(timeStamps),
        signalDatas(signalDatas)
    {}

    quint16 id;
    QVector<TimeStamp> timeStamps;
    QVector<SignalData> signalDatas;
};
}
