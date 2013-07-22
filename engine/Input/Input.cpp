#include <SDL.h>
#include "Input.h"

Input& Input::get_instance()
{
	static Input singleton( Lua::get_instance() );
	return singleton;
}

bool Input::register_key(wchar_t key, std::string path)
{
	keyMap[key] = path;
	return true;
}

#include <iostream>
//this function is used for luaponte binding
bool bind_register_key(std::string key, std::string path)
{
	Input& instance = Input::get_instance();
	instance.register_key(key[0], path);
	return true;
}

bool Input::key_pressed(wchar_t key) const
{
	return keyStates[key];
}

//this function is used for luaponte binding
bool bind_key_pressed(std::string key)
{
	Input& instance = Input::get_instance();
	return instance.key_pressed(key[0]);
}

bool Input::handle()
{
	SDL_PumpEvents();
	keyStates = SDL_GetKeyState(nullptr);

	//pressed keys handling
	for(auto& it : keyMap){
		if (keyStates[it.first] == true){
			lua.do_file(it.second);
		}
	}

	return true;
}
