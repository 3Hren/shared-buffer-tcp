#include "GetSignalDataResponseHandler.h"

#include "../Client.h"
#include "../../protocol/GetSignalDataResponseProtocol.h"

GetSignalDataResponseHandler::GetSignalDataResponseHandler(RequestProtocol *requestProtocol, Client *client, QTcpSocket *socket) :
    ClientSideResponseHandler(requestProtocol, client, socket)
{
}

void GetSignalDataResponseHandler::execute()
{
    GetSignalDataResponseProtocol *getSignalDataResponseProtocol = static_cast<GetSignalDataResponseProtocol *>(requestProtocol);

    const TimeStamp &requestTimeStamp = getSignalDataResponseProtocol->getTimeStamp();
    const quint8 &requestType = getSignalDataResponseProtocol->getRequestType();
    Response response(requestTimeStamp, requestType);

    const QVector<SignalData> &signalDatas = getSignalDataResponseProtocol->getSignalDatas();
    client->notifySignalDatas(response, signalDatas);
}
