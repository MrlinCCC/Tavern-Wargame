#include "GameCore.h"

using asio::ip::tcp;

GameRunner::GameRunner()
{
	conn_build();

}
inline void GameRunner::conn_build()
{
	tcp::resolver resolver(StaticManager::get_io_content());
	asio::ip::tcp::resolver::results_type m_endpoints = resolver.resolve(SERVER_IP, SERVER_PORT);
	p_socket = new tcp::socket(StaticManager::get_io_content());
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
	p_socket->read_some(asio::buffer(&is_matched, sizeof(bool)), StaticManager::get_error_code());
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
				ready = true;
				break;
			}
		}
		// 是否准备
		asio::write((*p_socket), asio::buffer(&ready, sizeof(bool)), StaticManager::get_error_code());
		if (ready)
			std::cout << "您已就绪！" << std::endl;
		p_socket->read_some(asio::buffer(&begin_game, sizeof(bool)), StaticManager::get_error_code());
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
void GameRunner::select_Hero()
{
	//展示
	int index[INIT_HERO_NUMS];
	std::cout << "please choose your hero:" << std::endl;
	for (int count = 0; count < INIT_HERO_NUMS; count++)
	{
		p_socket->read_some(asio::buffer(&index[count], sizeof(int)), StaticManager::get_error_code()); //传递三个英雄的下标
		std::cout << count + 1 << "、";
		StaticManager::get_hero_proxy().get_hero(index[count])->show_introduce();
	}
	//选择
	bool selected = false, overtime = false, finished = false;
	int input = 0;
	std::thread count_time([&selected, &overtime]() {
		Sleep(30000);
		if (!selected)
			overtime = true;
		});
	count_time.detach();
	std::thread accept_input(std::bind(&Util::accpet_int_between, std::ref(input), std::ref(selected), 1, INIT_HERO_NUMS + 1, true));
	accept_input.detach();
	while (!selected && !overtime);
	if (overtime && !selected) {
		input = Util::get_random(INIT_HERO_NUMS + 1);
		std::cout << "已超时，已自动选择英雄" << input << std::endl;
	}
	p_socket->write_some(asio::buffer(&index[input - 1], sizeof(int)), StaticManager::get_error_code());
	std::cout << "等待其他玩家选择英雄..." << std::endl;
	p_socket->read_some(asio::buffer(&finished, sizeof(bool)), StaticManager::get_error_code());
	std::cout << "游戏正式开始！" << std::endl;
	system("pause");
	system("cls");
}

void GameRunner::run_gamecore()
{
	select_Hero();
}


void GameRunner::run()
{
	int select;
	while (1) {
		show_indexPage();
		std::cout << "请选择：";
		std::cin >> select;
		asio::write((*p_socket), asio::buffer(&select, sizeof(int)), StaticManager::get_error_code());
		switch (select)
		{
		case 1: {
			system("cls");
			if (startMatch()) {
				run_gamecore();
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
}


asio::io_context& StaticManager::get_io_content()
{
	static asio::io_context sm_io_content;
	return sm_io_content;
}

asio::error_code& StaticManager::get_error_code()
{
	static asio::error_code error;
	return error;
}

HeroProxy& StaticManager::get_hero_proxy()
{
	static HeroProxy proxy;
	return proxy;
}



