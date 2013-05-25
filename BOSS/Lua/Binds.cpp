#include <luabind/luabind.hpp>
#include "Binds.h"
#include <string>
#include <iostream>

#include "../Input/Input.h"
bool bind_register_key(std::string key, std::string path)
{

	//получаем экземпляр input
	Input* instance = Input::init(nullptr);

	instance->register_key(key[0], path);

	return true;
}

bool bind_key_pressed(std::string key)
{
	//получаем экземпляр input
	Input* instance = Input::init(nullptr);

	return instance->key_pressed(key[0]);
}

void bind_class_input()
{
	//получаем экземпляр Lua
	Lua* instance = Lua::init();

	luabind::module(instance->get_state())
    [
		luabind::def("register_key", &bind_register_key),
		luabind::def("key_pressed", &bind_key_pressed)
    ];
}

#include "../NEW/ResourceManager/ResourceManager.h"
#include "../NEW/ResourceManager/AnimationResource.h"
bool bind_load_animation_resource(std::string path, std::wstring name)
{
	ResourceManager* instance = ResourceManager::init();

	return (instance->load_resource<AnimationResource>(path, name) != nullptr);
}

bool bind_load_image_resource(std::string path, std::wstring name)
{
	ResourceManager* instance = ResourceManager::init();

	return (instance->load_resource<ImageResource>(path, name) != nullptr);
}

void bind_class_resmngr()
{
	//получаем экземпляр Lua
	Lua* instance = Lua::init();

	luabind::module(instance->get_state())
    [
		luabind::def("load_animation_resource", &bind_load_animation_resource),
		luabind::def("load_image_resource", &bind_load_image_resource)
    ];
}