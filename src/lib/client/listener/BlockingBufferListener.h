#pragma once

#include "BlockingListener.h"

#include "protocol/Response.h"
#include "protocol/ErrorResponse.h"

#include "exceptions/ProtocolException.h"

#include <QSharedPointer>

//! @todo: сделать шаблонный класс на основе этого
namespace BufferStorage {
class Response;
class BufferClient;
class BlockingBufferListener : public BlockingListener
{
    Q_OBJECT
    QSharedPointer<Response> response;
public:
    BlockingBufferListener(int timeout, BufferClient *client, QObject *parent = 0);

    template<typename T>
    T getResponse() const {
        if (!response)
            throw BufferStorageException("Timeout");

        if (response->getType() == RESPONSE_ERROR) {
            ErrorResponse *errorResponse = static_cast<ErrorResponse *>(response.data());
            throw ProtocolException(errorResponse->getRequestType(), errorResponse->getErrorType(), errorResponse->getErrorMessage());
        }

        return static_cast<T>(response.data());
    }

    Q_SLOT void saveResponse(QSharedPointer<Response> response);
    Q_SLOT void saveErrorResponse(QSharedPointer<ErrorResponse> errorResponse);
};
}
