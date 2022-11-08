#include "Character.h"




Charactor::Charactor():m_glod(INIT_GOLD),m_life(FULL_LIFE),m_hero(nullptr)
{
	m_shop = new Shop();
}

Charactor::~Charactor()
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



void Charactor::buy(Minion* minion)
{
	//获取商店类传递的随从信息
	minions_rest.push_back(minion);
}
void Charactor::sell(int i)
{
	minions_fight.erase((minions_fight.begin() + i));
	m_glod += SELL_PRICE;
}

void Charactor::set_on(int i)
{
	minions_fight.push_back((minions_rest[i]));
	minions_rest.erase((minions_rest.begin() + i));
}
void Charactor::lift_down(int i)
{
	minions_rest.push_back((minions_rest[i]));
	minions_fight.erase((minions_rest.begin() + i));
}
void Charactor::show_minions() const
{

}


const std::vector<Minion*>& Charactor::get_fight() const
{
	return minions_fight;
}



