#include "GetSignalDataResponseHandler.h"

#include "../BufferClient.h"
#include "../BufferClientPrivate.h"
#include "../../protocol/GetSignalDataResponse.h"
#include "../struct/SignalDataResponse.h"

using namespace BufferStorage;

GetSignalDataResponseHandler::GetSignalDataResponseHandler(Request *requestProtocol, BufferClientPrivate *clientPrivate, QTcpSocket *socket) :
    ClientSideResponseHandler(requestProtocol, clientPrivate, socket)
{
}

void GetSignalDataResponseHandler::execute()
{
    GetSignalDataResponse *getSignalDataResponseProtocol = static_cast<GetSignalDataResponse *>(requestProtocol);

    const ProtocolType &requestType = getSignalDataResponseProtocol->getRequestType();
    const TimeStamp &timeStamp = getSignalDataResponseProtocol->getTimeStamp();
    const QVector<SignalData> &signalDatas = getSignalDataResponseProtocol->getSignalDatas();
    SignalDataResponse response(requestType, timeStamp, signalDatas);

    clientPrivate->callSignalDatasReceived(response);
}
