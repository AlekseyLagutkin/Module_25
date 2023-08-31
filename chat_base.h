#pragma once
#include <string>
#include <mysql.h>

class chat_base
{
public:
	chat_base();   
	MYSQL* con(const char* ip, const int port);   //Соединение с БД
	std::string select(const char* c);   //Получение строки из БД
	void out_str(const char* c, std::string title);   //Вывод строк из БД на экран
	MYSQL* get_des();   //Получение дескриптора
	~chat_base();

private:
	//const char* c;
	std::string str;
	MYSQL mysql;
	MYSQL_RES* res;
	MYSQL_ROW row;
};