#pragma once

#include "Request.h"

namespace BufferStorage {
class Response : public Request
{
protected:
    ProtocolType requestType;

public:
    Response(ProtocolType type, ProtocolType requestType);

    ProtocolType getRequestType() const;
};
}

#include <QSharedPointer>
Q_DECLARE_METATYPE(QSharedPointer<BufferStorage::Response>)
