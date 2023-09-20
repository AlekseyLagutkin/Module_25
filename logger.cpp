#include <fstream>
#include <thread>
#include "logger.h"

logger::logger()
{}

void logger::log_r(std::string fname)
{
	mt.lock_shared();
	std::thread t1([fname]() {std::fstream f; std::string s; f.open(fname); if (f.is_open()) { f >> s; std::cout << s << std::endl; } f.close(); });
	t1.join();
	mt.unlock_shared();
}

void logger::log_w(std::string fname, std::string s)
{
	mt.lock();
	std::thread t2([fname, s]() {std::fstream f; f.open(fname, std::ios::app); if (f.is_open()) { f << s << '\n'; } f.close(); });
	t2.join();
	mt.unlock();
}

logger::~logger()
{}
