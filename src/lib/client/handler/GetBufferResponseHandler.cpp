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
    const BufferId id = getBufferResponseProtocol->getBufferId();
    const TimeStampVector &timeStamps = getBufferResponseProtocol->getBufferTimeStamps();
    const SignalValueVector &datas = getBufferResponseProtocol->getBufferData();

    BufferResponse response(requestType, id, timeStamps, datas);

    clientPrivate->callBufferReceived(response);
}
