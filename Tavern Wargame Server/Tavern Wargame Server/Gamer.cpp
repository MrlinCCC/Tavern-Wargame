#include "Gamer.h"




Gamer::Gamer() :m_glod(INIT_GOLD), m_life(FULL_LIFE), m_hero(nullptr)
{
	m_shop = new Shop();
}

Gamer::~Gamer()
{
	if (m_hero) {
		delete m_hero;
		m_hero = nullptr;
	}
	if (m_shop) {
		delete m_shop;
		m_shop = nullptr;
	}
	for (auto& pmini : minions_fight)
		if (pmini) {
			delete pmini;
			pmini = nullptr;
		}
	for (auto& pmini : minions_rest)
		if (pmini) {
			delete pmini;
			pmini = nullptr;
		}
	for (auto& pmini : minions_enemy)
		if (pmini) {
			delete pmini;
			pmini = nullptr;
		}
}

void Gamer::set_hero(Hero* hero)
{
	m_hero = hero;
}



void Gamer::buy(Minion* minion)
{
	//获取商店类传递的随从信息
	minions_rest.push_back(minion);
}
void Gamer::sell(int i)
{
	minions_fight.erase((minions_fight.begin() + i));
	m_glod += SELL_PRICE;
}

void Gamer::set_on(int i)
{
	minions_fight.push_back((minions_rest[i]));
	minions_rest.erase((minions_rest.begin() + i));
}
void Gamer::lift_down(int i)
{
	minions_rest.push_back((minions_rest[i]));
	minions_fight.erase((minions_rest.begin() + i));
}
void Gamer::show_minions() const
{

}


const std::vector<Minion*>& Gamer::get_fight() const
{
	return minions_fight;
}



