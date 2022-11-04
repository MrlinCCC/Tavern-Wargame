#include "GameCore.h"

using asio::ip::tcp;
using namespace GameCore;
GameRunner::GameRunner()
{
}
tcp::socket GameCore::GameRunner::conn_build()
{
	asio::io_context io_context;
	tcp::resolver resolver(io_context);
	tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "14");
	tcp::socket socket(io_context);
	asio::connect(socket, endpoints);
	return socket;
}
void GameCore::GameRunner::run()
{
	// tcp::socket socket_run=conn_build();
	//show page
	//when start match
	startMatch(conn_build());
	Charactor charactor;
	Hero hero;
	select_Hero(hero, charactor, conn_build());
}

void GameCore::GameRunner::startMatch(tcp::socket socket)
{
	bool match = false,ready=true;
	//建立连接，返回match（true or false）
	std::cout << "正在匹配...";
	asio::read(socket, asio::buffer(&match, sizeof(bool)));
	system("cls");
	std::cout << "任意键确认您已经准备就绪";
	while (!_kbhit())
	{
		asio::write(socket, asio::buffer(&ready, sizeof(bool)));
		break;
	} //匹配成功开始游戏
}

void GameCore::GameRunner::select_Hero(Hero &hero, Charactor &charactor, tcp::socket socket)
{
	hero.init_hero();

	int getarr[3];
	std::cout << "please choose your hero" << std::endl;
	for (int i = 0; i < 3; i++)
	{
		asio::read(socket, asio::buffer(&getarr[i], sizeof(int))); //传递三个英雄的下标
	}

	for (int i = 0; i < 3; i++)
	{
		std::cout << std::endl;
		std::cout << std::endl;
	}
}

GameCore::Charactor::Charactor() : life(100), life_event(1), init_num_Entourage(0), init_num_gold(3) {}

void Charactor::buy(GameCore::Minion &entourage)
{
	//获取商店类传递的随从信息
	entourages_rest.push_back(entourage);
}
void Charactor::sell(int i)
{
	entourages_fight.erase((entourages_fight.begin() + i));
}
void Charactor::flash()
{
}
void Charactor::set_on(int i)
{
	entourages_fight.push_back((entourages_rest[i]));
	entourages_rest.erase((entourages_rest.begin() + i));
}
void Charactor::lift_down(int i)
{
	entourages_rest.push_back((entourages_rest[i]));
	entourages_fight.erase((entourages_rest.begin() + i));
}
void Charactor::show_entourages()
{
	//获取对面牌的数据

	asio::read(socket, asio::buffer(&entourages_enemy, sizeof(std::vector<Minion>)));
	std::cout << "敌方场上随从:" << std::endl;
	for (auto i : entourages_enemy)
	{
		std::cout << i.show_entourage();
	}
	std::cout << "我方场上随从：" << std::endl;
	for (auto i : entourages_fight)
	{
		//展示我方场上随从
		std::cout << i.show_entourage();
	}

	std::cout << "我方场下随从：" << std::endl;
	for (auto i : entourages_rest)
	{
		//展示我方场下随从
		std::cout << i.show_entourage();
	}
}

void GameCore::Charactor::get_hero_skill(hero &hero_skill)
{
	this->my_hero_skill = &hero_skill;
}

int GameCore::Charactor::get_life()
{

	return life;
}

void GameCore::Charactor::set_life(int l)
{
	this->life = l;
}

int GameCore::Charactor::get_gold()
{
	return init_num_gold;
}

void GameCore::Charactor::set_gold(int g)
{
	this->init_num_gold = g;
}

void GameCore::Charactor::set_life_event(bool le)
{
	this->life_event = le;
}

int GameCore::Charactor::get_num_Entourage()
{
	return init_num_Entourage;
}

void GameCore::Charactor::set_num_Entourage(int num)
{
	this->init_num_Entourage = num;
}

std::vector<Minion> &GameCore::Charactor::get_rest()
{
	return entourages_rest;
}

std::vector<Minion> &GameCore::Charactor::get_fight()
{
	return entourages_fight;
}

GameCore::Minion::Minion() : gold(1), aggressivity(1), life(1) {}

std::string Minion::show_entourage()
{
	return name + std::to_string(life) + std::to_string(aggressivity);
}

int GameCore::Minion::get_gold()
{
	return this->gold;
}

int GameCore::Minion::get_aggressivity()
{
	return this->aggressivity;
}

int GameCore::Minion::get_life()
{
	return this->life;
}

void GameCore::Minion::set_gold(int g)
{
	this->gold = g;
}

void GameCore::Minion::set_aggressivity(int a)
{
	this->aggressivity = a;
}

void GameCore::Minion::set_life(int l)
{
	this->life = l;
}

//给盾，随从加血加攻
void Hero::skill1(GameCore::Charactor &charactor)
{
	std::vector<GameCore::Minion> temp;
	charactor.set_life(105);
	temp = charactor.get_fight();
	for (auto i : temp) {
		i.set_life(i.get_life() + 1);
		i.set_aggressivity(i.get_aggressivity() + 1);
	}
}
//永久加圣盾
void Hero::skill2(GameCore::Charactor &charactor)
{

}
//将商店任意一张卡随机为另一张同星级卡
void Hero::skill3(GameCore::Charactor &charactor)
{

}
void Hero::set_hero(hero& h, std::string s, skill_type st)
{

	h.name = s;
	h.skill = st;
	Hero::hero_list.push_back(h);

}
void Hero::init_hero()
{
	/*Hero::set_hero(*new hero(), "lp", Hero::skill1);*/
	Hero::hero_list.push_back(hero("lp", "获得5点额外生命值，所有场上随从属性值加1", Hero::skill1));
	Hero::hero_list.push_back(hero("lc", "选择一名场上随从获得圣盾", Hero::skill2));
	Hero::hero_list.push_back(hero("lx", "将商店展示的随从之一转化为另一张同星级随从卡", Hero::skill3));
	Hero::hero_list.push_back(hero("liming", "将商店展示的随从之一转化为另一张同星级随从卡", Hero::skill3));
}