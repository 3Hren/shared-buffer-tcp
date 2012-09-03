#include "GetBufferResponseHandler.h"

#include "../Client.h"
#include "../../protocol/GetBufferResponseProtocol.h"

GetBufferResponseHandler::GetBufferResponseHandler(RequestProtocol *requestProtocol, Client *client, QTcpSocket *socket) :
    ClientSideResponseHandler(requestProtocol, client, socket)
{
}

void GetBufferResponseHandler::execute()
{
    GetBufferResponseProtocol *getBufferResponseProtocol = static_cast<GetBufferResponseProtocol *>(requestProtocol);

    const TimeStamp &requestTimeStamp = getBufferResponseProtocol->getTimeStamp();
    const quint8 &requestType = getBufferResponseProtocol->getRequestType();
    Response response(requestTimeStamp, requestType);

    const QVector<TimeStamp> &bufferTimeStamps = getBufferResponseProtocol->getBufferTimeStamps();
    const QVector<SignalData> &bufferDatas = getBufferResponseProtocol->getBufferData();
    BufferData bufferData(bufferTimeStamps, bufferDatas);
    client->notifyBuffer(response, bufferData);
}
