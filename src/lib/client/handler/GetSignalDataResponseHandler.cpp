#include "GetSignalDataResponseHandler.h"

#include "../BufferClient.h"
#include "../../protocol/GetSignalDataResponseProtocol.h"
#include "../struct/SignalDataResponse.h"

using namespace BufferStorage;

GetSignalDataResponseHandler::GetSignalDataResponseHandler(RequestProtocol *requestProtocol, BufferClient *client, QTcpSocket *socket) :
    ClientSideResponseHandler(requestProtocol, client, socket)
{
}

void GetSignalDataResponseHandler::execute()
{
    GetSignalDataResponseProtocol *getSignalDataResponseProtocol = static_cast<GetSignalDataResponseProtocol *>(requestProtocol);

    const quint8 &requestType = getSignalDataResponseProtocol->getRequestType();
    const TimeStamp &timeStamp = getSignalDataResponseProtocol->getTimeStamp();
    const QVector<SignalData> &signalDatas = getSignalDataResponseProtocol->getSignalDatas();
    SignalDataResponse response(requestType, timeStamp, signalDatas);

    client->signalDatasReceived(response);
}
