#pragma once
#include "include/asio.hpp"
#include <vector>
#include <iostream>
#include <conio.h>
#include <map>
#include <string>
#include<thread>
#include"Character.h"

const int INDEX_WIDTH = 60;
const int INDEX_HEIGH = 20;
const int OPTION_NUM = 3;
constexpr int MARGIN = INDEX_WIDTH / 2.5;
const std::string SERVER_IP = "127.0.0.1";
const std::string SERVER_PORT = "8888";

// Game类
class GameRunner
{

public:
	GameRunner();
	inline void conn_build();
	void show_indexPage();
	bool startMatch();
	void select_Hero(Charactor& charactor, asio::ip::tcp::socket socket);
	void run();
	~GameRunner();
private:
	Charactor m_chara;
	asio::io_context m_io_context;
	asio::ip::tcp::resolver::results_type m_endpoints;
	asio::ip::tcp::socket* p_socket;
};

