#pragma once
#include<iostream>
#include <vector>
#include"Shop.h"
#include"Hero.h"
#include"Minion.h"
constexpr int MAX_MINISION_NUM = 7;
constexpr int FULL_LIFE = 40;
constexpr int INIT_GOLD = 3;
constexpr int SELL_PRICE = 1;

class Hero;
class Shop;
//玩家类
class Gamer
{
public:
	Gamer();
	~Gamer();
	void buy(Minion* minion);
	void sell(int i);
	void flash();
	void set_on(int i);		//随从去战斗区
	void lift_down(int i);	//随从去休息区
	void battle_settlement();//  战斗结算
	void show_minions() const;
	void show_hero() const;
	void show_gold() const;
	void show_life() const;
	void show_rest() const;
	void show_fight() const;
	void show_shop() const;

	const std::vector<Minion*>& get_fight() const;

private:
	int m_life;
	int m_glod;
	Shop* m_shop;
	Hero* m_hero;
	std::vector<Minion*> minions_rest;
	std::vector<Minion*> minions_fight;
	std::vector<Minion*> minions_enemy;
	bool turn_is_win;
};

