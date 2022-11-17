#include "ServerRunner.h"


using asio::ip::tcp;

ServerRunner::ServerRunner() {

}

ServerRunner::~ServerRunner() {

}

void ServerRunner::run_server_core()
{
	//watch port
	std::thread wp(std::bind(watch_port, this));
	wp.detach();
	//match games
	std::thread mgs(std::bind(match_games, this));
	mgs.join();
}

void ServerRunner::run_game_core(Game* game)
{
	int sh_count = 0;
	bool sh_over = true;
	for (auto gamer_it = game->m_gamers.begin(); gamer_it != game->m_gamers.end(); gamer_it++) {
		std::thread sh(std::bind(&Game::select_hero, gamer_it, std::ref(sh_count)));
		sh.detach();
	}
	while (sh_count != GAME_CHARA_NUMS);
	for (auto& gamer : game->m_gamers) {
		gamer.first->write_some(asio::buffer(&sh_over, sizeof(bool)), StaticManager::get_error_code());
	}
	while (1);
	//when one gamer over,he should be rewatch indexpage
	for (auto gamer : game->m_gamers) {
		std::thread wi(std::bind(watch_indexpage, this, gamer.first));
		wi.detach();
	}
	delete game;
	game = nullptr;
}

inline void ServerRunner::set_ms(asio::ip::tcp::socket* psocket, MatchState ms)
{
	sockets_map[psocket] = ms;

}

inline void ServerRunner::start_matching(asio::ip::tcp::socket* p_socket)
{
	matching_que.push_back(p_socket);
	set_ms(p_socket, MatchState::Matching_State);
	std::cout << "matching " << matching_que.size() << std::endl;
}

inline void ServerRunner::exit(asio::ip::tcp::socket* p_socket)
{
	auto it = sockets_map.find(p_socket);
	delete (it->first);
	sockets_map.erase(it);
	std::cout << "online " << sockets_map.size() << std::endl;
}



void watch_port(ServerRunner* sc)
{
	asio::io_context& io_content = StaticManager::get_io_content();
	tcp::acceptor acceptor(io_content, tcp::endpoint(tcp::v4(), WATCH_PORT));
	while (1) {
		tcp::socket* psocket = new tcp::socket(io_content);
		acceptor.accept(*psocket);
		sc->sockets_map.insert(std::make_pair(psocket, MatchState::Null_State));
		std::cout << "online " << sc->sockets_map.size() << std::endl;
		std::thread wi(std::bind(watch_indexpage, sc, psocket));
		wi.detach();
	}
}

void watch_indexpage(ServerRunner* sc, asio::ip::tcp::socket* p_socket)
{
	int select;
	bool exit_condition = false;
	while (1) {
		asio::read(*p_socket, asio::buffer(&select, sizeof(int)), StaticManager::get_error_code());
		switch (select) {
		case 1: {//match
			sc->start_matching(p_socket);
			exit_condition = is_exit_watch_indexpage(sc, p_socket);
			break;
		}
		case 2: {
			break;
		}
		case 3: {//exit
			sc->exit(p_socket);
			break;
		}
		default: {
			std::cout << "select error " << select << std::endl;
		}
		}
		if (select == 3 || exit_condition)
			break;
	}
}

bool is_exit_watch_indexpage(ServerRunner* sc, asio::ip::tcp::socket* p_socket)
{
	//server add matching_state,client add exit matching button
	while (sc->sockets_map[p_socket] == MatchState::Matching_State);
	return sc->sockets_map[p_socket] == MatchState::Success_State;
}

void match_game(ServerRunner* sc)
{
	psockets gamers;
	bool  game_begin = false, match_success = true;
	int accept = 0, wait_over = 0, wa_over = 0;
	for (int i = 0; i < GAME_CHARA_NUMS; i++) {
		gamers.push_back(sc->matching_que.front());
		sc->matching_que.pop_front();
	}
	for (auto& gamer : gamers) {
		asio::write((*gamer), asio::buffer(&match_success, sizeof(bool)), StaticManager::get_error_code());
		//watch_accept
		std::thread wa([&]() {
			bool ready = false;
			gamer->read_some(asio::buffer(&ready, sizeof(bool)), StaticManager::get_error_code());
			if (ready)
				accept++;
			wait_over++;
			std::cout << "wait_over " << wait_over << std::endl;
			while (wait_over != GAME_CHARA_NUMS);//可阻塞
			if (accept == GAME_CHARA_NUMS) {
				//all accept
				game_begin = true;
				sc->set_ms(gamer, MatchState::Success_State);
			}
			else {
				if (ready)
					sc->matching_que.push_front(gamer);
				else {
					sc->set_ms(gamer, MatchState::Null_State);
				}
			}
			gamer->write_some(asio::buffer(&game_begin, sizeof(bool)), StaticManager::get_error_code());
			wa_over++;
			});
		wa.detach();
	}
	while (wa_over != GAME_CHARA_NUMS);
	if (game_begin) {
		sc->games.push_back(new Game(gamers));
		sc->run_game_core(sc->games.back());
	}
	gamers.clear();
}

void match_games(ServerRunner* sc)
{
	while (1) {
		if (sc->matching_que.size() >= GAME_CHARA_NUMS) {
			std::thread mg(std::bind(match_game, sc));
			mg.detach();
		}
		Sleep(1000);
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

std::random_device& StaticManager::get_random_device()
{
	static std::random_device rd;
	return rd;
}

Game::Game(psockets gamers)
{
	for (auto& gamer : gamers) {
		m_gamers.insert(std::make_pair(gamer, new Gamer()));
	}
}

Game::Game(psockets&& gamers)
{
	for (auto& gamer : gamers) {
		m_gamers.insert(std::make_pair(gamer, new Gamer()));
		gamer = nullptr;
	}
}

void Game::select_hero(gamer_iterator gamer, int& sh_count)
{
	{
		std::unordered_set<int> indexs;
		for (int count = 0; count < INIT_HERO_NUMS; count++) {
			int random = Util::get_random(StaticManager::get_hero_proxy().get_hero_nums());
			while (!indexs.insert(random).second) {
				random = Util::get_random(StaticManager::get_hero_proxy().get_hero_nums());
			};
			std::cout << "random" << random << std::endl;
			gamer->first->write_some(asio::buffer(&random, sizeof(int)), StaticManager::get_error_code());
		}
	}
	int index;
	gamer->first->read_some(asio::buffer(&index, sizeof(int)), StaticManager::get_error_code());
	gamer->second->set_hero(StaticManager::get_hero_proxy().clone(index));
	sh_count++;
}

