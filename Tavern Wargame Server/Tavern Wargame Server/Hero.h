#pragma once

#include"Gamer.h"
#include<iostream>
#include<vector>


class Hero
{
public:
	Hero(std::string name, std::string skill, std::string introduce);
	Hero(Hero& hero);
	void show_introduce() const;
	void use_skill();
private:
	std::string m_name;
	std::string m_skill;
	std::string m_introduce;
};

class HeroProxy {
public:
	HeroProxy();
	int get_hero_nums() const;
	Hero* clone(int index);

private:
	std::vector<Hero*> p_heroProxy;
};

