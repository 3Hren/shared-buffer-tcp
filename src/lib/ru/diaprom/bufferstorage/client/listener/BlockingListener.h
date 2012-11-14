#pragma once

#include <QObject>

#include "ru/diaprom/bufferstorage/protocol/Response.h"
#include "ru/diaprom/bufferstorage/protocol/ErrorResponse.h"

#include "ru/diaprom/bufferstorage/exceptions/ProtocolException.h"

#include <QSharedPointer>

namespace BufferStorage {
class Response;
class BufferClientImplementation;
class BlockingListener : public QObject
{    
    Q_OBJECT
    volatile bool listening;
    SharedResponse response;
public:
    BlockingListener(BufferClientImplementation *client, QObject *parent = 0);

    void listen(int timeout);

    template<typename T>
    T getResponse() const {
        if (!response)
            throw BufferStorageException("Timeout");

        if (response->getType() == RESPONSE_ERROR) {
            ErrorResponse *errorResponse = static_cast<ErrorResponse *>(response.data());
            throw ProtocolException(errorResponse->getRequestType(), errorResponse->getErrorType(), errorResponse->getReason());
        }

        return static_cast<T>(response.data());
    }

    Q_SLOT void stopListening();

private:
    Q_SLOT void saveResponse(SharedResponse response);
    Q_SLOT void saveErrorResponse(SharedErrorResponse errorResponse);
};
}
