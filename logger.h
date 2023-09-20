#pragma once

#include <iostream>
#include <shared_mutex>


class logger
{
public:
	logger();
	void log_r(std::string fname);   //Чтение строки из файла
	void log_w(std::string fname, std::string s);   //Запись сообщения в файл
	~logger();
private:
	std::shared_mutex mt;
};