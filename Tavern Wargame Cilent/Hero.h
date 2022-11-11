#pragma once

#include"Gamer.h"
#include<iostream>
#include<vector>


class Hero
{
public:
	void show_introduce() const;
	void use_skill();
private:
	std::string m_name;
	std::string m_skill;
	std::string m_introduce;
};


