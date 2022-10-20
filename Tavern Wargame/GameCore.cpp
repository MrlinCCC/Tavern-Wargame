#include "GameCore.h"
#include<iostream>

using namespace GameCore;

GameCore::Entourage::Entourage() {
	int aggressivity = 1;
	int life = 1;
}
void GameCore::Entourage::attack_Entourage()
{
	std::cout << "ok";
	//life -=aggressivity;
}

GameCore::Charactor::Charactor() :life(100), life_event(1), init_num_Entourage(0), init_num_gold(3) {}
