#pragma once

#include "Response.h"

#include "SignalData.h"

namespace BufferStorage {
struct SignalDataResponse : public Response
{
    SignalDataResponse() : Response() {}
    SignalDataResponse(quint8 requestType, TimeStamp timeStamp, const QVector<SignalData> &signalDatas) :
        Response(requestType),
        timeStamp(timeStamp),
        signalDatas(signalDatas)
      //Добавить еще массив индексов буферов
    {}

    TimeStamp timeStamp;
    QVector<SignalData> signalDatas;
};
}
