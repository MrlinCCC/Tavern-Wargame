#pragma once
class StaticManager {
public:
	static asio::io_context& get_io_content();
	static asio::error_code& get_error_code();
	static HeroProxy& get_hero_proxy();

};