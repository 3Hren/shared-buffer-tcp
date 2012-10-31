#include "GetSignalDataResponseHandler.h"

#include "../BufferClient.h"
#include "../BufferClientPrivate.h"
#include "../../protocol/GetSignalDataResponseProtocol.h"
#include "../struct/SignalDataResponse.h"

using namespace BufferStorage;

GetSignalDataResponseHandler::GetSignalDataResponseHandler(RequestProtocol *requestProtocol, BufferClientPrivate *clientPrivate, QTcpSocket *socket) :
    ClientSideResponseHandler(requestProtocol, clientPrivate, socket)
{
}

void GetSignalDataResponseHandler::execute()
{
    GetSignalDataResponseProtocol *getSignalDataResponseProtocol = static_cast<GetSignalDataResponseProtocol *>(requestProtocol);

    const quint8 &requestType = getSignalDataResponseProtocol->getRequestType();
    const TimeStamp &timeStamp = getSignalDataResponseProtocol->getTimeStamp();
    const QVector<SignalData> &signalDatas = getSignalDataResponseProtocol->getSignalDatas();
    SignalDataResponse response(requestType, timeStamp, signalDatas);

    clientPrivate->callSignalDatasReceived(response);
}
