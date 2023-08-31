#include <iostream>
#include <string>
#include <mysql.h>
#include "in_chat.h"

in_chat::in_chat(chat_base* _cb, int _id): cb(_cb), id(_id)
{
	id1 = std::to_string(id);
	str1 = "SELECT name, surname, email FROM users WHERE id=" + id1;
	c = str1.c_str();
	cb->out_str(c, "-----------------------------------------");
}

void in_chat::s_mes()   //Отправка сообщений
{
	mysql = cb->get_des();   //Получение дескриптора
	char in;
	int i;
	while (true)
	{
		str1 = "SELECT date, email, text FROM users JOIN message on users.id=message.rec_id where send_id=" + id1;   //Вывод отправленных сообщений
		c = str1.c_str();
		cb->out_str(c, "Отправленные сообщения");

		str1 = "SELECT date, email, text FROM users JOIN message on users.id=message.send_id where rec_id=" + id1;   //Вывод принятых сообщений
		c = str1.c_str();
		cb->out_str(c, "Принятые сообщения");


		std::cout << "Для отправки сообщения введите 1, для выхода введите 2:" << std::endl;   //Отправка сообщений
		std::cin >> in;
		if (in == '1')
		{
			std::cout << "Введите логин пользователя, которому вы хотите отправить сообщение,\n";
			std::cout << "или введите all для отправки всем пользователям:\n";
			std::cin >> login;
			str1 = "SELECT id FROM users WHERE email ='" + login + "'";   //Получение id получателя
			c = str1.c_str();
			mysql_query(mysql, c);
			if (res = mysql_store_result(mysql))
			{
				if (row = mysql_fetch_row(res))
				{
					id2 = row[0];
					std::cout << "Введите сообщение:";
					std::cin >> mes;
					str1 = "INSERT INTO message (send_id, rec_id, text, date, status) VALUES (" + id1 + ", " + id2 + ", '" + mes + "', current_date, 1)";
					c = str1.c_str();
					mysql_query(mysql, c);
				}
				else if (login == "all")
				{
					std::cout << "Введите сообщение:";
					std::cin >> mes;
					str1 = "SELECT id FROM users WHERE id !=" + id1;   //Получение id всех пользователей, кроме отправителя
					c = str1.c_str();
					mysql_query(mysql, c);
					if (res = mysql_store_result(mysql))
					{
						while (row = mysql_fetch_row(res))
						{
							for (i = 0; i < mysql_num_fields(res); i++)
							{
								str1 = "INSERT INTO message (send_id, rec_id, text, date, status) VALUES (" + id1 + ", " + row[i] + ", '" + mes + "', current_date, 1)";
								c = str1.c_str();
								mysql_query(mysql, c);
							}
						}
					}
				}
				else
				{
					std::cout << "Такого пользователя не существует." << std::endl;
				}
			}
			else
			{
				std::cout << "Ошибка MySql номер " << mysql_error(mysql);
			}
		}
		if (in == '2')
		{
			break;
		}
	}
}
in_chat::~in_chat()
{}