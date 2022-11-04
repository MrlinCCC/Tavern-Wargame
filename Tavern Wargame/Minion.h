#pragma once
#include<iostream>
#include<string>

constexpr int pGold = 3;

enum class Blood {
	NullBlood=0,
	Beast=1,
	Demon=2,
	Dragon=3,
	Mechine=4,
	FishMan=5,
	Elem=6,
	Cana=7,
	All=8
};



std::string show_blood(Blood blood);

class Minion
{
public:
	Minion();
	Minion(std::string name, int attack, int life,Blood blood,std::string effect,
		 bool shiled, bool double_attck, bool revive, bool prior_attackted);
	~Minion();

	std::string show_info(); //展示当前随从

	int get_attack() const;
	int get_life() const;

	bool is_shiled;//圣盾
	bool is_double_attack;//风怒
	bool is_revive;//复生
	bool is_prior_attacked;//嘲讽

private:
	std::string m_name;
	int m_gold;		  //所需金币
	int m_attack; //攻击力
	int m_life;		  //生命力
	Blood m_blood;//种族
	std::string m_effct;//效果脚本名，路径固定
};

