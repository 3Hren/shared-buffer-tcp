# Buffer Storage
Библиотека и прикладные приложения для создания и работы с клиент/серверной связкой циклического буфера сигналов.
Включает в себя TCP-сервер и API для доступа к нему.

Для корректной сборки и запуска тестов необходим компилятор с поддержкой некоторых фич стандарта C++11: списки инициализации и лямбда функции.

Сам сервер не требует C++11.

#### Сборка
	:::java
	qmake
	make
	make install

Для использования клиентского API необходимо подключить заголовочный файл BufferClient.h

#### Пример (асинхронная отправка сообщений)
	:::java
	#include <BufferClient.h>

	using namespace BufferStorage;

	// Где-то создаем экземпляр класса клиента и устанавливаем подключение к серверу
	BufferClient *client = new BufferClient;
	connect(client, SIGNAL(errorReceived(SharedErrorResponse)), SLOT(handleError(SharedErrorResponse)));
	client->blockingConnectToServer();

	...

	TimeStamp timeStamp(QDateTime::currentDateTime().toTime_t()); 
	SignalValueVector signalValues;
	signalValues.fill(SignalValue(5.5, 0), 100); // Заполняем вектор сигналов
	client->push(signalValues, timeStamp); 

#### Пример (блокирующее получение буфера)
	:::java
	#include <BufferClient.h>

	using namespace BufferStorage;

	...

	BufferClient *client = new BuffetClient;
	client->blockingConnectToServer();

	try {
		BufferId bufferId = 150;
		const SignalBuffer &signalBuffer = client->blockingGetBuffer(bufferId);
		// обработка полученного буфера
	} catch (BufferStorageException &exception) {
		// обработка ошибки
	}

В случае блокирующего запроса ответ возвращается прямо из функции. Если произойдет ошибка, то будет выброшено исключение.
В случае неблокирующего запроса как ответ, так и возможные ошибки будут посланы как сигналы.
