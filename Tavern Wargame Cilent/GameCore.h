#pragma once
#include "include/asio.hpp"
#include <vector>
#include <iostream>
#include <conio.h>
#include <map>
#include <string>
#include<thread>
#include<random>
#include"Gamer.h"

const int INDEX_WIDTH = 60;
const int INDEX_HEIGH = 20;
const int OPTION_NUM = 3;
constexpr int MARGIN = INDEX_WIDTH / 2.5;
const std::string SERVER_IP = "127.0.0.1";
const std::string SERVER_PORT = "8888";
const int INIT_HERO_NUMS = 2;

// Game类
class GameRunner
{
public:
	GameRunner();
	inline void conn_build();
	void show_indexPage();
	bool startMatch();
	void select_Hero();
	void run_gamecore();
	void run();
	~GameRunner();
private:
	Gamer* m_gamer;
	asio::ip::tcp::socket* p_socket;
};

class StaticManager {
public:
	static asio::io_context& get_io_content();
	static asio::error_code& get_error_code();
	static HeroProxy& get_hero_proxy();
};

class Util {
public:
	static void accpet_int_between(int& input, bool& finished, int low, int high, bool assure) {
		while (1) {
			if (_kbhit) {
				input = _getch() - '0';
				if (input >= low && input < high) {
					//是否为确认输入
					if (assure) {
						int ass = -1;
						std::cout << "确认选择 " << input << "吗？(1、确认，0、取消)" << std::endl;
						while (1) {
							if (_kbhit) {
								ass = _getch() - '0';
							}
							if (ass == 1) {
								std::cout << "你已选择" << input << std::endl;
								finished = true;
								break;
							}
							else if (ass == 0)
								std::cout << "已取消选择，请重新选择!" << std::endl;
						}
					}
					else {
						finished = true;
						break;
					}
				}
			}
			else
				std::cout << "input error! please input again!" << std::endl;
			if (finished)
				break;
		}
	}
	static int get_random(int max) {
		std::random_device rd;
		return rd() % max;
	}
};

