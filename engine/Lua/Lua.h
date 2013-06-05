#ifndef _LUA_H_
#define _LUA_H_

#include <string>
#include <Lua.hpp>

class Lua{
public:
	//creates singleton
	static Lua* get_instance(){
		static Lua singleton;
		return &singleton;
	}

	//executes the script
	bool do_file(const std::string& path);

	lua_State* get_state() const{ return this->state; };

	//binds the classes and methods
	void bind_all();

private:
	lua_State* state;

	//hide it(singleton)
	Lua();
	~Lua();
	Lua(const Lua&) = delete;
	Lua& operator=(const Lua&) = delete;
};

#endif