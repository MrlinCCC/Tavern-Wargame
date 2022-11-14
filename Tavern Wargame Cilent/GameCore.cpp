#include "GameCore.h"

using asio::ip::tcp;

GameRunner::GameRunner()
{
	conn_build();

}
inline void GameRunner::conn_build()
{
	tcp::resolver resolver(m_io_context);
	asio::ip::tcp::resolver::results_type m_endpoints = resolver.resolve(SERVER_IP, SERVER_PORT);
	p_socket = new tcp::socket(m_io_context);
	asio::connect(*p_socket, m_endpoints);
}

void GameRunner::show_indexPage()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD ord;
	_CONSOLE_SCREEN_BUFFER_INFO* p_info = new _CONSOLE_SCREEN_BUFFER_INFO();
	GetConsoleScreenBufferInfo(handle, p_info);
	int console_X = p_info->dwMaximumWindowSize.X, console_Y = p_info->dwMaximumWindowSize.Y;
	int index_left_top_x = (console_X - INDEX_WIDTH) / 2, index_left_top_y = (console_Y - INDEX_HEIGH) / 2,
		index_right_bottom_x = (console_X + INDEX_WIDTH) / 2, index_right_bottom_y = (console_Y + INDEX_HEIGH) / 2;
	for (int i = -(INDEX_WIDTH / 2); i <= INDEX_WIDTH / 2; i++) {
		ord.X = console_X / 2 + i;
		for (int j = -(INDEX_HEIGH / 2); j <= INDEX_HEIGH / 2; j++) {
			ord.Y = console_Y / 2 + j;
			SetConsoleCursorPosition(handle, ord);
			if (ord.X == index_left_top_x || ord.X == index_right_bottom_x ||
				ord.Y == index_left_top_y || ord.Y == index_right_bottom_y)
				std::cout << "*";
		}
	}
	int internal = INDEX_HEIGH / (OPTION_NUM + 1);
	std::vector<std::string> options;
	options.push_back("1、开始匹配");
	options.push_back("2、人机对战");
	options.push_back("3、退出游戏");
	ord.X = index_left_top_x + MARGIN, ord.Y = index_left_top_y + internal;
	for (int count = 0; count < OPTION_NUM; count++, ord.Y += internal) {
		SetConsoleCursorPosition(handle, ord);
		std::cout << options[count];
	}
	ord.X = index_left_top_x + 1, ord.Y = index_right_bottom_y + 1;
	SetConsoleCursorPosition(handle, ord);
}

GameRunner::~GameRunner()
{

}

bool GameRunner::startMatch()
{
	bool is_matched = false, ready = false, over_time = false, begin_game = true;
	std::cout << "正在匹配..." << std::endl;
	p_socket->read_some(asio::buffer(&is_matched, sizeof(bool)), error);
	//已匹配
	if (is_matched) {
		std::thread count_time([&ready, &over_time]() {
			Sleep(10000);
			if (!ready)
				over_time = true;
			});
		count_time.detach();
		std::cout << "任意键确认您已经准备就绪" << std::endl;
		while (!over_time)
		{
			if (_kbhit()) {
				std::cout << _getch() << std::endl;
				ready = true;
				break;
			}
		}
		// 是否准备
		asio::write((*p_socket), asio::buffer(&ready, sizeof(bool)), error);
		if (ready)
			std::cout << "您已就绪！" << std::endl;
		p_socket->read_some(asio::buffer(&begin_game, sizeof(bool)), error);
		std::cout << "begin_game has read" << std::endl;
		if (over_time)
			std::cout << "您未确认就绪，请重新匹配!" << std::endl;
		else if (begin_game)
			std::cout << "游戏即将开始!" << std::endl;
		else {
			std::cout << "有其他玩家未确认就绪，已重新匹配!" << std::endl;
			begin_game = startMatch();
		}
		return begin_game;
	}
}
void GameRunner::select_Hero(Gamer& gamer, tcp::socket socket)
{
	int getarr[3];
	std::cout << "please choose your hero" << std::endl;
	for (int i = 0; i < 3; i++)
	{
		asio::read(socket, asio::buffer(&getarr[i], sizeof(int))); //传递三个英雄的下标
	}

	for (int i = 0; i < 3; i++)
	{
		std::cout << std::endl;
		std::cout << std::endl;
	}
}


void GameRunner::run()
{
	int select;
	while (1) {
		show_indexPage();
		std::cout << "请选择：";
		std::cin >> select;
		asio::write((*p_socket), asio::buffer(&select, sizeof(int)), error);
		switch (select)
		{
		case 1: {
			system("cls");
			if (startMatch()) {

			}
			else
				system("pause");
			break;
		}
		case 2: {
			break;
		}
		case 3: {
			exit(0);
			break;
		}
		default: {
			std::cout << "输入有误,请重新选择!";
			system("pause");
			system("cls");
			break;
		}
		}
	}
	//gamer gamer;
	//Hero hero;
	//select_Hero( gamer, conn_build());
}


