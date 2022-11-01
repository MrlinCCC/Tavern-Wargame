#include "Hero.h"


using skill_type = void(*)(GameCore::Charactor);
//给盾，随从加血加攻
static std::vector<Hero::hero> hero_list;
void Hero::skill1(GameCore::Charactor charactor)
{
	std::vector<GameCore::Entourage> temp;
	charactor.set_life(105);
	temp = charactor.get_fight();
	for (auto i : temp) {
		i.set_life(i.get_life() + 1);
		i.set_aggressivity(i.get_aggressivity()+1);
	}
}
//永久加圣盾
void Hero::skill2(GameCore::Charactor charactor)
{

}
//将商店任意一张卡随机为另一张同星级卡
void Hero::skill3(GameCore::Charactor charactor)
{
	
}
void Hero::set_hero(hero &h,std::string s,skill_type st)
{
	
	h.name = s;
	h.skill = st;
	Hero::hero_list.push_back(h);
	
}
void Hero::init_hero()
{
	/*Hero::set_hero(*new hero(), "lp", Hero::skill1);*/
	Hero::hero_list.push_back(Hero::hero("lp","获得5点额外生命值，所有场上随从属性值加1", Hero::skill1));
	Hero::hero_list.push_back(Hero::hero("lc","选择一名场上随从获得圣盾", Hero::skill2));
	Hero::hero_list.push_back(Hero::hero("lx","将商店展示的随从之一转化为另一张同星级随从卡", Hero::skill3));
	Hero::hero_list.push_back(Hero::hero("liming", "将商店展示的随从之一转化为另一张同星级随从卡", Hero::skill3));
}


