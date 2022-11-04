#include "GameCore.h"

using asio::ip::tcp;

GameRunner::GameRunner()
{
}
tcp::socket GameRunner::conn_build()
{
	asio::io_context io_context;
	tcp::resolver resolver(io_context);
	tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "14");
	tcp::socket socket(io_context);
	asio::connect(socket, endpoints);
	return socket;
}
void GameRunner::run()
{

	// tcp::socket socket_run=conn_build();
	//show page
	//when start match
	//startMatch(conn_build());
	//Charactor charactor;
	//Hero hero;
	//select_Hero( charactor, conn_build());
}

GameRunner::~GameRunner()
{
}

void GameRunner::startMatch(tcp::socket socket)
{
	bool match = false,ready=true;
	//建立连接，返回match（true or false）
	std::cout << "正在匹配...";
	asio::read(socket, asio::buffer(&match, sizeof(bool)));
	system("cls");
	std::cout << "任意键确认您已经准备就绪";
	while (!_kbhit())
	{
		asio::write(socket, asio::buffer(&ready, sizeof(bool)));
		break;
	} //匹配成功开始游戏
}

void GameRunner::select_Hero( Charactor &charactor, tcp::socket socket)
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


