#pragma once
#include "include/asio.hpp"
#include <vector>
#include <iostream>
#include <conio.h>
#include <map>
#include <string>

namespace GameCore
{
	//随从类
	class Minion
	{
	public:
		// Entourage(int x, int y) :aggressivity(x), life(y) {};
		Minion();
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


	using skill_type = void(*)(GameCore::Charactor&);
	typedef struct hero {
		std::string name;
		std::string skill_describe;
		skill_type skill;
		struct hero() = default;
		struct hero(std::string name, std::string skill_describe, skill_type skill) :name(name), skill_describe(skill_describe), skill(skill)
		{

		};
	}hero;


	class Hero
	{

	public:
		std::vector<hero> hero_list;
		skill_type skill1_temp;


		static void skill1(GameCore::Charactor& charactor);
		static void skill2(GameCore::Charactor& charactor);
		static void skill3(GameCore::Charactor& charactor);
		void set_hero(hero& h, std::string s, skill_type st);
		void init_hero();
	};

	//玩家类
	class Charactor
	{
	public:
		Charactor();

		void attack_c(); // Player attack
		void buy(Minion& entourage);
		void sell(int i);
		void flash();
		void set_on(int i);		//随从去战斗区
		void lift_down(int i);	//随从去休息区
		void show_entourages(); //展示所有随从
		void show_hero(); //展示英雄信息4
		void get_hero_skill(hero& hero_skill);
		int get_life();
		void set_life(int l);
		int get_gold();
		void set_gold(int g);
		void set_life_event(bool le);
		int get_num_Entourage();
		void set_num_Entourage(int num);
		std::vector<Minion>& get_rest();
		std::vector<Minion>& get_fight();

	private:
		int life;
		bool life_event;		//存活状态(living or die)
		int init_num_Entourage; //初始随从上限
		int init_num_gold;		//初始金币数量
		std::vector<Minion> entourages_rest;
		std::vector<Minion> entourages_fight;
		std::vector<Minion> entourages_enemy;
		hero* my_hero_skill;
	};

	//商城
	class Shop
	{
	public:
		Shop();

	private:
		std::map<int, Minion*> entourages;
	};

	// Game类
	class GameRunner
	{

	public:
		GameRunner();
		asio::ip::tcp::socket conn_build();
		void startMatch( asio::ip::tcp::socket socket);
		void select_Hero(Hero &hero, Charactor &charactor, asio::ip::tcp::socket socket);
		void run();
		~GameRunner();
	private:
	};


}