#include "ServerCore.h"
#include<iostream>

using asio::ip::tcp;

void ServerCore::run()
{
	bool match = true;
	asio::io_context io_context;
	tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), WATCH_PORT));
	tcp::socket socket(io_context);
	acceptor.accept(socket);
	std::cout << "连接成功" << std::endl;
	int res = asio::write(socket, asio::buffer(&match, sizeof(bool)));
	std::cout << "match 发送成功" << std::endl;
	std::cout << res << std::endl;
	Sleep(50000);
}
