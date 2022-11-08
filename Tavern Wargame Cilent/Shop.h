#pragma once
#include"Minion.h"


class Shop
{
public:
	Shop();
	~Shop();

private:
	int m_level;
	int minions_num;
	std::vector<Minion*> minion_onsell;
};

