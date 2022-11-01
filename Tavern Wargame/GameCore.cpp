#include "GameCore.h"
#include<iostream>

using asio::ip::tcp;
using namespace GameCore;
Game_Life_Line::Game_Life_Line(){
	
	
	
}
tcp::socket GameCore::Game_Life_Line::conn_build()
{
	asio::io_context io_context;
	tcp::resolver resolver(io_context);
	tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "14");
	tcp::socket socket(io_context);
	asio::connect(socket, endpoints);
	return socket;
}
void GameCore::Game_Life_Line::run()
{
	//tcp::socket socket_run=conn_build();
	startMatch(false, true,conn_build());
	Charactor charactor;
	Hero hero;
	select_Hero(hero,charactor,conn_build());
}

void GameCore::Game_Life_Line::startMatch(bool match,bool ready,tcp::socket socket) {
	//建立连接，返回match（true or false）
	std::cout << "正在匹配...";
	asio::read(socket, asio::buffer(&match, sizeof(bool)));
	system("cls");
	std::cout << "任意键确认您已经准备就绪";
	while (!_kbhit()) {
		asio::write(socket, asio::buffer(&ready, sizeof(bool)));
		break;
	}//匹配成功开始游戏
}

void GameCore::Game_Life_Line::select_Hero(Hero &hero ,Charactor& charactor, tcp::socket socket)
{
	hero.init_hero();
	
	int getarr[3];
	std::cout << "please choose your hero" << std::endl;
	for (int i = 0; i < 3; i++) {
		asio::read(socket, asio::buffer(&getarr[i], sizeof(int)));//传递三个英雄的下标
	}
	
	for (int i = 0; i < 3;i++) {
		std::cout << <<std::endl;
		std::cout << << std::endl;
	}
}





GameCore::Charactor::Charactor() :life(100), life_event(1), init_num_Entourage(0), init_num_gold(3) {}

void Charactor::buy(GameCore::Entourage &entourage) {
	//获取商店类传递的随从信息
	entourages_rest.push_back(entourage);
}
void Charactor::sell(int i) {
	entourages_fight.erase((entourages_fight.begin()+i));
}
void Charactor::flash() {
	
}
void Charactor::set_on(int i) {
	entourages_fight.push_back((entourages_rest[i]));
	entourages_rest.erase((entourages_rest.begin()+i));
	
}
void Charactor::lift_down(int i) {
	entourages_rest.push_back((entourages_rest[i]));
	entourages_fight.erase((entourages_rest.begin() + i));
}
void Charactor::show_entourages() {
	//获取对面牌的数据

	asio::read(socket,asio::buffer(&entourages_enemy, sizeof(std::vector<Entourage>)));
	std::cout << "敌方场上随从:" << std::endl;
	for (auto i : entourages_enemy)
	{
		std::cout << i.show_entourage();
	}
	std::cout << "我方场上随从："<<std::endl;
	for (auto i : entourages_fight) {
		//展示我方场上随从
		std::cout << i.show_entourage();
	}
	
	std::cout << "我方场下随从："<< std::endl;
	for (auto i : entourages_rest) {
		//展示我方场下随从
		std::cout << i.show_entourage();
	}
}

void GameCore::Charactor::get_hero_skill(Hero::hero&hero_skill)
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


std::vector<Entourage> &GameCore::Charactor::get_rest()
{
	return entourages_rest ;
}

std::vector<Entourage> &GameCore::Charactor::get_fight()
{
	return entourages_fight;
}

GameCore::Entourage::Entourage() :gold(1), aggressivity(1), life(1) {}


std::string Entourage::show_entourage (){
	return name +std::to_string(life)+std::to_string(aggressivity);
}

int GameCore::Entourage::get_gold()
{
	return this->gold;
}

int GameCore::Entourage::get_aggressivity()
{
	return this->aggressivity;
}

int GameCore::Entourage::get_life()
{
	return this->life;
}

void GameCore::Entourage::set_gold(int g)
{
	this->gold = g;
}

void GameCore::Entourage::set_aggressivity(int a)
{
	this->aggressivity = a;
}

void GameCore::Entourage::set_life(int l)
{
	this->life = l;
}
