#pragma once
#include "GameCore.h"
class Hero
{
	using skill_type = void(Hero::*)(GameCore::Charactor);
public:
	typedef struct hero {
		std::string name;
		std::string skill_describe;
		skill_type skill;
		struct hero() = default;
		struct hero(std::string name, std::string skill_describe, skill_type skill) :name(name),skill_describe(skill_describe), skill(skill)
		{

		};
	}hero;
	static std::vector<hero> hero_list;
	void skill1(GameCore::Charactor charactor);
	skill_type skill1_temp;

	void skill2(GameCore::Charactor charactor);
	void skill3(GameCore::Charactor charactor);
	
	void set_hero(hero &h, std::string s, skill_type st);
	void init_hero();
};


