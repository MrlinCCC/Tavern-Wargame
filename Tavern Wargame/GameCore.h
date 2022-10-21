#pragma once
#include<vector>
namespace GameCore {

	//Game类
	class Game_Life_Line {
	public:
		Game_Life_Line();
		void startMatch(bool match);
		void getReady();
	private:
		bool match;//是否匹配到对手
		bool ready;//是否准备就绪

	};

	//随从基类
	class Entourage {
	public:
		//Entourage(int x, int y) :aggressivity(x), life(y) {};
		Entourage();
		//Entourage attack;


		void attack_Entourage();//攻击敌方随从
		void be_attacked_Entourage(int aggressivity_enemy);//我方随从被攻击
		void show();
		
	private:
		int aggressivity;//攻击力
		int life;//生命力
		
	};
	//玩家类
	class Charactor {
	public :
		Charactor();
		void attack_c();//Player attack
		void buy();
		void sell();
		void flash();
		void set_on();
		void lift_down();
			
	private:
		int life;
		bool life_event;//存活状态(living or die)
		int init_num_Entourage;//初始随从数量
		int init_num_gold;//初始金币数量
		std::vector<Charactor*> entourages_rest;
		std::vector<Charactor*> entourages_fight;
	};

}