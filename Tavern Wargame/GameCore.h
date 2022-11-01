#pragma once

#include "Hero.h"
#include <vector>
//#include<windows.h>
#include <conio.h>
#include "include/asio.hpp"
#include <map>
#include <string>
namespace GameCore
{
	class Charactor;

	// Game类
	class Game_Life_Line
	{

	public:
		Game_Life_Line();
		asio::ip::tcp::socket conn_build();
		void startMatch(bool match, bool ready, asio::ip::tcp::socket socket);
		void select_Hero(Hero &hero, Charactor &charactor, asio::ip::tcp::socket socket);
		void run();

	private:
	};
	class Entourage;
	class Shop
	{
	public:
		Shop();

	private:
		std::map<int, Entourage *> entourages;
	};
	//随从基类
	class Entourage
	{
	public:
		// Entourage(int x, int y) :aggressivity(x), life(y) {};
		Entourage();
		// Entourage attack;
		std::string show_entourage(); //展示当前随从

		void attack_Entourage();							//攻击敌方随从
		void be_attacked_Entourage(int aggressivity_enemy); //我方随从被攻击
		int get_gold();
		int get_aggressivity();
		int get_life();
		void set_gold(int g);
		void set_aggressivity(int a);
		void set_life(int l);

	private:
		std::string name;

		int gold;		  //所需金币
		int aggressivity; //攻击力
		int life;		  //生命力
	};

	//玩家类
	class Charactor
	{

		using chara_skill = void (*)(Charactor &);

	public:
		Charactor();

		void attack_c(); // Player attack
		void buy(Entourage &entourage);
		void sell(int i);
		void flash();
		void set_on(int i);		//随从去战斗区
		void lift_down(int i);	//随从去休息区
		void show_entourages(); //展示所有随从

		void show_hero(); //展示英雄信息4
		void get_hero_skill(Hero::hero &hero_skill);
		int get_life();
		void set_life(int l);
		int get_gold();
		void set_gold(int g);
		void set_life_event(bool le);
		int get_num_Entourage();
		void set_num_Entourage(int num);

		std::vector<Entourage> &get_rest();
		std::vector<Entourage> &get_fight();

	private:
		chara_skill now_skill;
		int life;
		bool life_event;		//存活状态(living or die)
		int init_num_Entourage; //初始随从上限
		int init_num_gold;		//初始金币数量
		std::vector<Entourage> entourages_rest;
		std::vector<Entourage> entourages_fight;
		std::vector<Entourage> entourages_enemy;
		Hero::hero *my_hero_skill;
	};

}