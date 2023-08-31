#pragma once
#include <string>
#include <mysql.h>

class chek_us   //Регистрация и вход пользователей в чат
{
public:
	chek_us(MYSQL* _mysql);
	int chek_logpas();   //Вход пользователя
	int chek_in();   //Регистрация нового пользователя
	~chek_us();
private:
	std::string log;
	std::string pas;
	std::string str1;
	std::string str2;
	const char* c;
	MYSQL* mysql;
	MYSQL_RES* res;
	MYSQL_ROW row;
};
