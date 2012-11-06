#include "GetBufferResponseHandler.h"

#include "client/BufferClient.h"
#include "client/BufferClientPrivate.h"

#include "protocol/GetBufferResponse.h"

using namespace BufferStorage;

GetBufferResponseHandler::GetBufferResponseHandler(Request *requestProtocol, BufferClientPrivate *clientPrivate, QTcpSocket *socket) :
    ClientSideResponseHandler(requestProtocol, clientPrivate, socket)
{
}

void GetBufferResponseHandler::execute()
{
    GetBufferResponse *getBufferResponseProtocol = static_cast<GetBufferResponse *>(requestProtocol);

    const ProtocolType requestType = getBufferResponseProtocol->getRequestType();
    const quint16 id = getBufferResponseProtocol->getBufferId();
    const QVector<TimeStamp> &timeStamps = getBufferResponseProtocol->getBufferTimeStamps();
    const QVector<SignalData> &datas = getBufferResponseProtocol->getBufferData();

    BufferResponse response(requestType, id, timeStamps, datas);

    clientPrivate->callBufferReceived(response);
}
