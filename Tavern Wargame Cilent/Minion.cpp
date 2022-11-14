#include "Minion.h"


Minion::Minion(std::string name, int attack, int life, int star, Blood blood, std::string effect, Etype etype,
	bool shiled, bool double_attck, bool revive, bool prior_attackted)
	:m_name(name), m_attack(attack), m_life(life), m_level(1), m_star(star), m_blood(blood), m_effct(effect), m_etype(etype) {
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
	return "随从名：" + m_name +
		"血量：" + std::to_string(m_life) +
		"攻击：" + std::to_string(m_attack) +
		"种族：" + show_blood(m_blood);
}

int Minion::get_attack() const
{
	return this->m_attack;
}

int Minion::get_life() const
{
	return this->m_life;
}

void Minion::trigger_effect(std::vector<Minion*> minions)
{
	scs::interpreter in;

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

MinionProxy::MinionProxy(Minion* pTarget)
{
	this->pminion = pTarget;
}

Minion* MinionProxy::get_proxy()
{
	return this->pminion;
}
