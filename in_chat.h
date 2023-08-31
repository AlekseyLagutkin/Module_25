#pragma once
#include <string>
#include <mysql.h>
#include "chat_base.h"

class in_chat   //Отправка и просмотр сообщений
{
public:
	in_chat(chat_base* _cb, int _id);   //id пользователя
	void s_mes();   //Отправка сообщений
	~in_chat();

private:
	std::string login;
	std::string name;
	std::string mes;
	std::string str1;
	std::string id1;
	std::string id2;
	const char* c;
	int id;
	chat_base* cb;
	MYSQL* mysql;
	MYSQL_RES* res;
	MYSQL_ROW row;
};