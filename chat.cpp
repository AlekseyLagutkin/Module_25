#include <iostream>
#include "mysql.h"
#include "chat_base.h"
#include "chek_us.h"
#include "in_chat.h"

int main()
{
	setlocale(LC_ALL, "");
	const char* ip = "127.0.0.1";
	const int port = 3306;
	int id;
	MYSQL* descr;
	chat_base db;
	descr = db.con(ip, port);   //Получение дескриптора соединения с БД

	std::cout << "Добро пожаловать в чат!\n";
	char in = 0;
	while (true)
	{
		std::cout << "Для входа в чат введите 1, для регистрации введите 2, для завершения работы введите 3:" << std::endl;
		std::cin >> in;
		if (in == '3')
		{
			break;
		}
		if (in == '1')
		{
			chek_us User(descr);
			id = User.chek_logpas();   //Проверка логина и пароля
			if (id > 0)
			{
				in_chat Uchat(&db, id);
				Uchat.s_mes();   //Отправка сообщений
			}

		}
		if (in == '2')
		{
			chek_us User(descr);
			User.chek_in();   //Добавление нового пользователя
		}
	}
	return 0;
}