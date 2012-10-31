# Buffer Storage
Библиотека и прикладные приложения для создания и работы с клиент/серверной связкой циклического буфера сигналов.
Включает в себя TCP-сервер и API для доступа к нему.

#### Пример (асинхронная отправка сообщений)
	:::java
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

#### Пример (блокирующее получение буфера)
	:::java
	BufferClient *client = new BuffetClient;
	connect(client, SIGNAL(error(ErrorResponse)), SLOT(showError(ErrorResponse)));
	client->blockingConnectToServer();

	...

	quint16 bufferId = 1;
	const BufferResponse &response = client->blockingGetBuffer(bufferId);
	qDebug() << response.timeStamps << response.signalDatas;

В случае блокирующего запроса ответ возвращается прямо из функции. Если произойдет ошибка, то будет выброшено исключение.
В случае неблокирующего запроса как ответ, так и возможные ошибки будут посланы как сигналы.




