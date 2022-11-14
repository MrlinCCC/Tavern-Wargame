#pragma once
#include"include/asio.hpp"
#include<iostream>
#include<thread>
#include<functional>
#include<deque>
#include<queue>
#include<unordered_map>
#include<algorithm>
#include"Hero.h"

const int WATCH_PORT = 8888;
const int GAME_CHARA_NUMS = 2;
const int INIT_HERO_NUMS = 2;

class ServerCore;
enum class MatchState;

using psockets = std::vector<asio::ip::tcp::socket*>;
using psockets_map = std::unordered_map<asio::ip::tcp::socket*, MatchState>;

void watch_port(ServerCore* sc);
void watch_indexpage(ServerCore* sc, asio::ip::tcp::socket* p_socket);
bool is_exit_watch_indexpage(ServerCore* sc, asio::ip::tcp::socket* p_socket);
void match_games(ServerCore* sc);
void match_game(ServerCore* sc);

class StaticManager {
public:
	static asio::io_context& get_io_content();
	static asio::error_code& get_error_code();
	static HeroProxy& get_hero_proxy();
};

class Game {
	friend class ServerCore;
public:
	Game(psockets gamers);
	Game(psockets&& gamers);
	void select_hero(asio::ip::tcp::socket* gamer);
private:
	psockets m_gamers;

};

enum  class MatchState
{
	Matching_State = 0,//正在匹配
	Success_State = 1,//正在游戏
	Null_State = 2//停在主页
};

class ServerCore
{
public:
	ServerCore();
	void run_server_core();
	void run_game_core(Game* game);
	inline void set_ms(asio::ip::tcp::socket* psocket, MatchState ms);
	inline void start_matching(asio::ip::tcp::socket* p_socket);
	inline void exit(asio::ip::tcp::socket* p_socket);
	~ServerCore();
	psockets_map sockets_map;
	std::deque<asio::ip::tcp::socket*> matching_que;
	std::vector<Game*> games;
};
