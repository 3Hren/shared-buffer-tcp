#include "GetBufferResponseHandler.h"

#include "../BufferClient.h"
#include "../../protocol/GetBufferResponseProtocol.h"

using namespace BufferStorage;

GetBufferResponseHandler::GetBufferResponseHandler(RequestProtocol *requestProtocol, BufferClient *client, QTcpSocket *socket) :
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

    client->bufferReceived(response);
}
