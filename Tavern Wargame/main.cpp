#include<iostream>
#include"GameCore.h"
using namespace std;

int main() {
	GameCore::Game_Life_Line *game = new GameCore::Game_Life_Line();
	game->startMatch(false,true);
	GameCore::Charactor* charactor = new GameCore::Charactor();
	game->init_Charactor(charactor);
	
}