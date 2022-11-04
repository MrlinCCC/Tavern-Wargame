#pragma once
#include "include/asio.hpp"
#include <vector>
#include <iostream>
#include <conio.h>
#include <map>
#include <string>
#include"Character.h"

// Game类
class GameRunner
{

public:
	GameRunner();
	asio::ip::tcp::socket conn_build();
	void startMatch( asio::ip::tcp::socket socket);
	void select_Hero(Charactor &charactor, asio::ip::tcp::socket socket);
	void run();
	~GameRunner();
private:
	Charactor m_chara;
};

