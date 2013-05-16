#ifndef _LUA_H_
#define _LUA_H_

#include <string>
#include <lua.hpp>

class Lua{
public:
	//создает единственный экземпл€р класса
	static Lua* init();

	//выполн€ет скрипт
	bool do_file(std::string path);

private:
	//декстриптор 
	lua_State* state;

	//скрываем (синглтон же)
	Lua() {};
	~Lua();
	Lua(const Lua&) {};
	Lua& operator=(const Lua&) {};
};

#endif