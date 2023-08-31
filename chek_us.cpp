#include <iostream>
#include <string>
#include <mysql.h>
#include "chek_us.h"
#include "chat_base.h"

chek_us::chek_us(MYSQL* _mysql): mysql(_mysql)
{
}
int chek_us::chek_logpas()   //Вход пользователя
{
	std::cout << "Введите логин:";
	std::cin >> log;
	bool login = false;
	bool pasw = false;
	int id;   //id пользователя
	str1 = "SELECT id FROM users WHERE email='" + log + "'";   //Запрос логина
	c = str1.c_str();
	mysql_query(mysql, c);   
	if (res = mysql_store_result(mysql))
	{
		if (row = mysql_fetch_row(res)) 
		{
			login = true;
			str2 = row[0];
			std::cout << "Введите пароль:";
			std::cin >> pas;
			str1 = "SELECT user_id FROM hash WHERE user_id='" + str2 + "' and hash='"+pas+"'";   //Запрос пароля
			c = str1.c_str();
			mysql_query(mysql, c);
			if (res = mysql_store_result(mysql))
			{
				if (row = mysql_fetch_row(res))
				{
					pasw = true;
					str2 = row[0];
				}
				id=std::stoi(str2);
			}
		}
		if (login == false)
		{
			std::cout << "Неверный логин" << std::endl;
			return 0;
		}
		else if (pasw == false)
		{
			std::cout << "Неверный пароль" << std::endl;
			return 0;
		}
		else
		{
			std::cout << "Вход выполнен\n" << std::endl;
			return id;
		}
	}
	else
	{
		std::cout << "Ошибка MySql номер " << mysql_error(mysql);
	}
	return -1;
}

int chek_us::chek_in()   //Регистрация нового пользователя
{
	bool login = true;
	int i;
	std::string pas2;
	std::string name;
	std::string surname;
	std::cout << "Введите логин:" << std::endl;
	std::cin >> log;
	str1 = "SELECT id FROM users WHERE email='" + log + "'";
	c = str1.c_str();
	mysql_query(mysql, c);
	if (res = mysql_store_result(mysql))
	{
		if (row = mysql_fetch_row(res))
		{
			std::cout << "Логин уже занят" << std::endl;
		}
		else
		{
			std::cout << "Введите ваше имя:";
			std::cin >> name;
			std::cout << "Введите вашу фамилию:";
			std::cin >> surname;
			std::cout << "Введите пароль:";
			std::cin >> pas;
			std::cout << "Подтвердите пароль:";
			std::cin >> pas2;
			if (pas2 == pas)
			{
				str1 = "INSERT INTO users (name, surname, email) VALUES ('" + name + "', '" + surname + "', '" + log + "')";   //Ввод данных пользователя
				c = str1.c_str();
				mysql_query(mysql, c);
				str1 = "UPDATE hash SET hash = '" + pas + "' where user_id = (select id from users where email = '" + log + "')";   //Запись пароля в таблицу hash
				c = str1.c_str();
				mysql_query(mysql, c);
				//std::cout << "Регистрация прошла успешно!" << std::endl;
				return 0;
			}
			else
			{
				std::cout << "Неверный пароль, регистрация прервана." << std::endl;
			}
		}

	}
	else
	{
		std::cout << "Ошибка MySql номер " << mysql_error(mysql);
	}
	return -1;

}

chek_us::~chek_us()
{}
