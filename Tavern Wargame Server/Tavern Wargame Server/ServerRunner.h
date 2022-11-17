#pragma once
#include"include/asio.hpp"
#include<iostream>
#include<thread>
#include<functional>
#include<deque>
#include<queue>
#include<unordered_map>
#include<algorithm>
#include<unordered_set>
#include<random>
#include"Hero.h"

const int WATCH_PORT = 8888;
const int GAME_CHARA_NUMS = 2;
const int INIT_HERO_NUMS = 2;

class ServerRunner;
enum class MatchState;

using psockets = std::vector<asio::ip::tcp::socket*>;
using gamer_iterator = std::unordered_map<asio::ip::tcp::socket*, Gamer*>::iterator;

void watch_port(ServerRunner* sc);
void watch_indexpage(ServerRunner* sc, asio::ip::tcp::socket* p_socket);
bool is_exit_watch_indexpage(ServerRunner* sc, asio::ip::tcp::socket* p_socket);
void match_games(ServerRunner* sc);
void match_game(ServerRunner* sc);

class Game {
	friend class ServerRunner;
public:
	Game(psockets gamers);
	Game(psockets&& gamers);
	static void select_hero(gamer_iterator gamer, int& sh_count);
private:
	std::unordered_map<asio::ip::tcp::socket*, Gamer*> m_gamers;
};

enum  class MatchState
{
	Matching_State = 0,//正在匹配
	Success_State = 1,//正在游戏
	Null_State = 2//停在主页
};

class ServerRunner
{
public:
	ServerRunner();
	void run_server_core();
	void run_game_core(Game* game);
	inline void set_ms(asio::ip::tcp::socket* psocket, MatchState ms);
	inline void start_matching(asio::ip::tcp::socket* p_socket);
	inline void exit(asio::ip::tcp::socket* p_socket);
	~ServerRunner();
	std::unordered_map<asio::ip::tcp::socket*, MatchState> sockets_map;
	std::deque<asio::ip::tcp::socket*> matching_que;
	std::vector<Game*> games;
};


class StaticManager {
public:
	static asio::io_context& get_io_content();
	static asio::error_code& get_error_code();
	static HeroProxy& get_hero_proxy();
	static std::random_device& get_random_device();
};

class Util {
public:
	static long get_random(int max) {
		std::random_device rd;
		return rd() % max;
	}
};
