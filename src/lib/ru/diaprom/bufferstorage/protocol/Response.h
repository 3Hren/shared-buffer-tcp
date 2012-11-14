#pragma once

#include "ProtocolMessage.h"

namespace BufferStorage {
class Response : public ProtocolMessage
{
protected:
    ProtocolType requestType;

public:
    Response(ProtocolType type, ProtocolType requestType);

    ProtocolType getRequestType() const;
};
}

#include <QSharedPointer>
typedef QSharedPointer<BufferStorage::Response> SharedResponse;
Q_BS_REGISTER_METATYPE(SharedResponse)
