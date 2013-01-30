#include "GetDataDumpResponse.h"

using namespace BufferStorage;

GetDataDumpResponse::GetDataDumpResponse() :
    Response(RESPONSE_GET_DATA_DUMP, REQUEST_GET_DATA_DUMP)
{
}

GetDataDumpResponse::GetDataDumpResponse(const TimeStampVector &timeStamps, const QHash<BufferId, SignalValueVector> &dataDump) :
    Response(RESPONSE_GET_DATA_DUMP, REQUEST_GET_DATA_DUMP),
    timeStamps(timeStamps),
    dataDump(dataDump)
{
}

TimeStampVector GetDataDumpResponse::getTimeStamps() const
{
    return timeStamps;
}

QHash<BufferId, SignalValueVector> GetDataDumpResponse::getDataDump() const
{
    return dataDump;
}

void GetDataDumpResponse::encodeData(QDataStream *out) const
{    
    *out << timeStamps << dataDump;
}

void GetDataDumpResponse::decodeData(QDataStream *in)
{
    *in >> timeStamps >> dataDump;
}
