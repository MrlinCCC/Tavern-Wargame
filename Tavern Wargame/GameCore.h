#pragma once
#include<vector>
#include<windows.h>
#include<conio.h>
#include"include/asio.hpp"
#include<map>
namespace GameCore {

	//Game类
	class Game_Life_Line {
	public:
		Game_Life_Line();
		void startMatch(bool match, bool ready);
		void init_Charactor(Charactor * charactor);

	private:
		

	};
	class Shop
	{
	public:
		Shop();
		

	private:
		std::map<int, Entourage*> entourages;

	};
	//随从基类
	class Entourage {
	public:
		//Entourage(int x, int y) :aggressivity(x), life(y) {};
		Entourage();
		//Entourage attack;


		void attack_Entourage();//攻击敌方随从
		void be_attacked_Entourage(int aggressivity_enemy);//我方随从被攻击
		
	private:
		int gold;//所需金币
		int aggressivity;//攻击力
		int life;//生命力
		
	};
	//玩家类
	class Charactor {
	public :
		Charactor();
		void attack_c();//Player attack
		void buy(Entourage *entourage);
		void sell(int i);
		void flash();
		void set_on(int i);
		void lift_down();
		void show_entourage();//
	private:
		int life;
		bool life_event;//存活状态(living or die)
		int init_num_Entourage;//初始随从数量
		int init_num_gold;//初始金币数量
		std::vector<Entourage*> entourages_rest;
		std::vector<Entourage*> entourages_fight;
	};

}