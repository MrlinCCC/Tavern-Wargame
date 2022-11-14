#include "Hero.h"

Hero::Hero(std::string name, std::string skill, std::string introduce) :m_name(name), m_skill(m_skill), m_introduce(introduce)
{
}

Hero::Hero(Hero& hero) : m_name(hero.m_name), m_skill(hero.m_skill), m_introduce(hero.m_introduce)
{
}

HeroProxy::HeroProxy()
{
}

int HeroProxy::get_hero_nums() const
{
	return p_heroProxy.size();
}

Hero* HeroProxy::clone(int index)
{
	return new Hero(*p_heroProxy[index]);
}
