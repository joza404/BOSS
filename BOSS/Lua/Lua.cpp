#include <iostream>
#include <luabind/luabind.hpp>

#include "Lua.h"

//создает единственный экземпл€р класса
Lua* Lua::init()
{
	static Lua singleView;
	static bool classCreated = false;

	//если класс уже создан
	if (classCreated == true) return &singleView;

	//инициалиризуем Lua
	singleView.state = luaL_newstate();
    luaL_openlibs(singleView.state);

	//прив€зываем к Luabind
	luabind::open(singleView.state);

#ifdef _DEBUG
	std::cout << "Lua загружен." << std::endl;
#endif

	classCreated = true;

	return &singleView;
}

//выполн€ет скрипт
bool Lua::do_file(std::string path)
{
	if (this->state == nullptr)
		return false;

	luaL_dofile(this->state,path.c_str());

	return true;
}

//деструктор
Lua::~Lua()
{
	lua_close(state);

#ifdef _DEBUG
	std::cout << "Lua выгружен." << std::endl;
#endif
}
