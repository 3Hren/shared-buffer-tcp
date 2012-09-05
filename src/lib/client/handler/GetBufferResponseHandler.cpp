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

    const quint8 requestType = getBufferResponseProtocol->getRequestType();
    const quint16 id = getBufferResponseProtocol->getBufferId();
    const QVector<TimeStamp> &timeStamps = getBufferResponseProtocol->getBufferTimeStamps();
    const QVector<SignalData> &datas = getBufferResponseProtocol->getBufferData();

    BufferResponse response(requestType, id, timeStamps, datas);

    client->notifyBuffer(response);
}
