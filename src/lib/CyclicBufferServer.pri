DEFINES += \
    BUFFER_CLIENT_DEBUG \
    BUFFER_SERVER_DEBUG

HEADERS += \
    exceptions/ServerCouldNotStartException.h \
    exceptions/ServerException.h \
    Runnable.h \
    server/BufferManager.h \
    Global.h \
    Buffer.h \
    exceptions/BufferNotFoundException.h \
    exceptions/Exception.h \
    exceptions/BufferException.h \
    SignalData.h \
    exceptions/WrongRequestTypeException.h \
    exceptions/ProtocolException.h \
    ConnectionHandler.h \
    RequestHandler.h \
    protocol/PushRequestProtocol.h \
    protocol/RequestProtocolFactory.h \
    protocol/RequestProtocol.h \
    protocol/ErrorMessageRequestProtocol.h \
    server/Server.h \
    client/Client.h \
    server/ServerConnectionHandler.h \
    client/ClientConnectionHandler.h \
    server/ServerSideRequestHandlerFactory.h \
    exceptions/WrongPushedDataSizeException.h \
    client/ClientSideRequestHandlerFactory.h \
    protocol/GetSignalDataRequestProtocol.h \
    protocol/GetSignalDataResponseProtocol.h \    
    exceptions/WrongTimeStampException.h \
    protocol/GetBufferRequestProtocol.h \
    protocol/GetBufferResponseProtocol.h \    
    client/handler/GetSignalDataResponseHandler.h \
    client/handler/GetBufferResponseHandler.h \
    client/handler/ErrorMessageResponseHandler.h \
    server/handler/PushRequestHandler.h \
    server/handler/GetSignalDataRequestHandler.h \
    server/handler/GetBufferRequestHandler.h \
    client/handler/ClientSideResponseHandler.h \
    server/handler/ServerSideRequestHandler.h \
    server/buffer/HashTableBufferManager.h \
    server/buffer/TreeBufferManager.h \
    FixedSizeQueue.h \
    client/listener/BlockingBufferListener.h \
    client/struct/Response.h \
    client/struct/BufferResponse.h \
    client/struct/ErrorResponse.h \
    client/struct/SignalDataResponse.h \
    protocol/ResponseProtocol.h \
    exceptions/ClientNotConnectedException.h

SOURCES += \
    ConnectionHandler.cpp \
    RequestHandler.cpp \
    protocol/PushRequestProtocol.cpp \
    protocol/RequestProtocolFactory.cpp \
    protocol/RequestProtocol.cpp \
    protocol/ErrorMessageRequestProtocol.cpp \
    server/ServerConnectionHandler.cpp \
    client/ClientConnectionHandler.cpp \
    server/Server.cpp \
    client/Client.cpp \
    server/ServerSideRequestHandlerFactory.cpp \
    client/ClientSideRequestHandlerFactory.cpp \
    protocol/GetSignalDataRequestProtocol.cpp \
    protocol/GetSignalDataResponseProtocol.cpp \
    protocol/GetBufferRequestProtocol.cpp \
    protocol/GetBufferResponseProtocol.cpp \
    client/handler/GetSignalDataResponseHandler.cpp \
    client/handler/GetBufferResponseHandler.cpp \
    client/handler/ErrorMessageResponseHandler.cpp \
    server/handler/PushRequestHandler.cpp \
    server/handler/GetSignalDataRequestHandler.cpp \
    server/handler/GetBufferRequestHandler.cpp \
    client/handler/ClientSideResponseHandler.cpp \
    server/handler/ServerSideRequestHandler.cpp \
    server/buffer/HashTableBufferManager.cpp \
    server/buffer/TreeBufferManager.cpp \
    client/listener/BlockingBufferListener.cpp \
    client/struct/Response.cpp \
    client/struct/BufferResponse.cpp \
    client/struct/ErrorResponse.cpp \
    client/struct/SignalDataResponse.cpp \
    protocol/ResponseProtocol.cpp
