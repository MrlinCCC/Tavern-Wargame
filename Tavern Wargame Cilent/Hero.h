#pragma once

#include"Gamer.h"
#include<iostream>
#include<vector>


class Hero
{
public:
	Hero(std::string name, std::string skill, std::string introduce, int shiled);
	void show_introduce() const;
	void use_skill();
private:
	std::string m_name;
	std::string m_skill;
	std::string m_introduce;
	int m_shiled;
};


