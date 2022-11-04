#include "Minion.h"

Minion::Minion() : m_gold(pGold){}

Minion::Minion(std::string name,int attack, int life, Blood blood,std::string effect,bool shiled,bool double_attck,bool revive,bool prior_attackted)
	:m_name(name), m_gold(pGold) ,m_attack(attack),m_life(life),m_blood(blood),m_effct(effect){
	is_shiled = shiled;
	is_double_attack = double_attck;
	is_revive = revive;
	is_prior_attacked = prior_attackted;
}

Minion::~Minion()
{
}



std::string Minion::show_info()
{
	return "随从名："+ m_name +
		"血量：" +std::to_string(m_life) +
		"攻击：" +std::to_string(m_attack)+
		"种族："+show_blood(m_blood);
}

int Minion::get_attack() const
{
	return this->m_attack;
}

int Minion::get_life() const
{
	return this->m_life;
}


std::string show_blood(Blood blood)
{
	switch (blood)
	{
	case Blood::NullBlood:
		return "无";
	case Blood::Beast:
		return "野兽";
	case Blood::Demon:
		return "恶魔";
	case Blood::Dragon:
		return "龙";
	case Blood::Elem:
		return "元素";
	case Blood::FishMan:
		return "鱼人";
	case Blood::Mechine:
		return "机械";
	case Blood::Cana:
		return "迦娜";
	case Blood::All:
		return "全能";
	default:
		break;
	}
}
