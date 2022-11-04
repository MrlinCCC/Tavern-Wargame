#include<iostream>
#include"GameCore.h"
#include"scs/scs/scs.hpp"
using namespace std;
using namespace scs;
void script_test() {
	scs::interpreter in;
	in.add_type<GameCore::Minion>("encourage");
	in.add_type<vector<GameCore::Minion>>("encourages");
	in.add_type<GameCore::Charactor>("character");
	in.add_function("inc_attack", { "encourages"}, false, [](backend::context& vc, const std::vector<backend::variable>& args) -> backend::variable
		{
			auto re = args[args.size() - 1];
			auto ti = vc.get_type(re.type_name);
			auto pre = ti.default_construction_func();
			ti.copy_func(pre, re.pcontent);
			return vc.move_existed_unnamed_variable(backend::variable(ti.type_name, pre)).to_constant();
		});
	in.run_from_file("../script/test.scs");
}

int main() {
	GameCore::GameRunner game;
	game.run();
	script_test();
	return 0;
}