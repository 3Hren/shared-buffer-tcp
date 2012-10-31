# Buffer Storage
Библиотека и прикладные приложения для создания и работы с клиент/серверной связкой циклического буфера сигналов.
Включает в себя TCP-сервер и API для доступа к нему.

#### Пример (асинхронная отправка сообщений)
	using namespace BufferStorage;

	// Где-то создаем экземпляр класса клиента и устанавливаем подключение к серверу
	BufferClient *client = new BufferClient;
	connect(client, SIGNAL(error(ErrorResponse)), SLOT(showError(ErrorResponse)));
	client->blockingConnectToServer();

	...

	QVector<SignalData> signalDatas;
	... // Заполняем вектор
	TimeStamp timeStamp = QDateTime::currentDateTime().toTime_t();
        client->push(signalDatas, timeStamp); 
