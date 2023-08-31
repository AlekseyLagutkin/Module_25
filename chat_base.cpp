#include <iostream>
#include <string>
#include "mysql.h"
#include "chat_base.h"

chat_base::chat_base()
{
}
MYSQL* chat_base::con(const char* ip, const int port)   //Соединение с БД, получение дескриптора
{
	mysql_init(&mysql);
	if (&mysql == nullptr)
	{
		std::cout << "Error: can't create descriptor" << std::endl;
	}
	if (!mysql_real_connect(&mysql, ip, "root", "ber2412", "chatbase", port, NULL, 0))
	{
		std::cout << "Error: can't connect to database " << mysql_error(&mysql) << std::endl;
	}
	else
	{
		std::cout << "Соединение с БД установлено" << std::endl;
	}
	!mysql_set_character_set(&mysql, "utf8");
	return &mysql;
}

std::string chat_base::select(const char* c)   //Получение строки из БД, с - строка запроса
{
	int i;
	mysql_query(&mysql, c);
	if (res = mysql_store_result(&mysql))
	{
		while (row = mysql_fetch_row(res))
		{
			for (i = 0; i < mysql_num_fields(res); i++)
			{
				str = row[i];
			}
		}
		return str;
	}
	else
	{
		std::cout << "Ошибка MySql номер " << mysql_error(&mysql);
	}
	return 0;
}

void chat_base::out_str(const char* c, std::string title)   //Вывод строк из БД на экран
{
	int i;
	mysql_query(&mysql, c);
	if (res = mysql_store_result(&mysql))
	{
		std::cout << title << std::endl << std::endl;   //Вывод заголовка
		while (row = mysql_fetch_row(res))
		{
			for (i = 0; i < mysql_num_fields(res); i++)
			{
				std::cout << row[i] << std::endl;
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	else
	{
		std::cout << "Ошибка MySql номер " << mysql_error(&mysql);
	}
}

MYSQL* chat_base::get_des()
{
	return &mysql;
}

chat_base::~chat_base()
{
	mysql_close(&mysql);
}