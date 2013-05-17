#include <luabind/luabind.hpp>
#include "Binds.h"
#include <string>
#include <iostream>

#include "../Input/Input.h"
bool bind_register_key(std::string key, std::string path)
{

	//�������� ��������� input
	Input* instance = Input::init(nullptr);

	instance->register_key(key[0], path);

	return true;
}

bool bind_key_pressed(std::string key)
{
	//�������� ��������� input
	Input* instance = Input::init(nullptr);

	return instance->key_pressed(key[0]);
}

void bind_class_input()
{
	//�������� ��������� Lua
	Lua* instance = Lua::init();

	luabind::module(instance->get_state())
    [
		luabind::def("register_key", &bind_register_key),
		luabind::def("key_pressed", &bind_key_pressed)
    ];
}