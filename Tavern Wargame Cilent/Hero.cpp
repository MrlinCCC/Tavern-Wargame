#include "Hero.h"

Hero::Hero(std::string name, std::string skill, int sk_cost, int shiled, std::string introduce)
	:m_name(name), m_skill(m_skill), m_sk_cost(sk_cost), m_shield(shiled), m_introduce(introduce)
{
}

Hero::Hero(Hero& hero) : m_name(hero.m_name), m_skill(hero.m_skill),
m_sk_cost(hero.m_sk_cost), m_shield(hero.m_shield), m_introduce(hero.m_introduce)
{
}

void Hero::show_introduce() const
{
	std::cout << "英雄:" << m_name << ",  " << "技能:" << m_skill << ",  " <<
		"技能介绍：" << m_introduce << std::endl;
}


HeroProxy::HeroProxy()
{
	std::ifstream ifs("./resource/hero.txt", std::ios::in);
	if (!ifs.is_open())
		throw("file open error!");
	std::string name, skill, introduce;
	int sk_cost, shiled;
	while (!ifs.eof()) {
		ifs >> name >> skill >> sk_cost >> shiled >> introduce;
		p_heroProxy.push_back(std::move(new Hero(name, skill, sk_cost, shiled, introduce)));
	}
	ifs.close();
}

int HeroProxy::get_hero_nums() const
{
	return p_heroProxy.size();
}

Hero* HeroProxy::get_hero(int index) const
{
	return p_heroProxy[index];
}

Hero* HeroProxy::clone(int index)
{
	return new Hero(*p_heroProxy[index]);
}
