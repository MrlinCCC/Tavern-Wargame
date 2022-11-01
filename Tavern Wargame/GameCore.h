#pragma once
#include <vector>
#include <windows.h>
#include <conio.h>
#include "include/asio.hpp"
#include <map>
namespace GameCore
{

	// Game��
	class Game_Life_Line
	{
	public:
		Game_Life_Line();
		void startMatch(bool match, bool ready);
		void init_Charactor(Charactor *charactor);

	private:
	};
	class Shop
	{
	public:
		Shop();

	private:
		std::map<int, Entourage *> entourages;
	};
	//��ӻ���
	class Entourage
	{
	public:
		// Entourage(int x, int y) :aggressivity(x), life(y) {};
		Entourage();
		// Entourage attack;

		void attack_Entourage();							//�����з����
		void be_attacked_Entourage(int aggressivity_enemy); //�ҷ���ӱ�����

	private:
		int gold;		  //������
		int aggressivity; //������
		int life;		  //������
	};
	//�����
	class Charactor
	{
	public:
		Charactor();
		void attack_c(); // Player attack
		void buy(Entourage *entourage);
		void sell(int i);
		void flash();
		void set_on(int i);
		void lift_down();
		void show_entourage(); //
	private:
		int life;
		bool life_event;		//���״̬(living or die)
		int init_num_Entourage; //��ʼ�������
		int init_num_gold;		//��ʼ�������
		std::vector<Entourage *> entourages_rest;
		std::vector<Entourage *> entourages_fight;
	};

}