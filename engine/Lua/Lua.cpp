#include <memory>

#include <Lua.hpp>
#include <luaponte\luaponte.hpp>

#include "Lua.h"

#include "../ResourceManager/ResourceManager.h"
#include "../ResourceManager/AnimationResource.h"
#include "../ResourceManager/ImageResource.h"
#include "../ResourceManager/FontResource.h"

#include "../Components/ComponentManager.h"
#include "../Components/Animation/Animation.h"
#include "../Components/Image/Image.h"
#include "../Components/Position/Position.h"
#include "../Components/Text/Text.h"


//creates singleton
Lua* Lua::get_instance()
{
	static Lua singleton;
	static bool classCreated = false;
	if (classCreated == true) return &singleton;

	//init lua and luaponte
	singleton.state = luaL_newstate();
    luaL_openlibs(singleton.state);
	luaponte::open(singleton.state);

	classCreated = true;
	return &singleton;
}

//executes a script
bool Lua::do_file(const std::string& path)
{
	if (this->state == nullptr)
		return false;

	luaL_dofile(this->state,path.c_str());

	return true;
}

Lua::~Lua()
{
	lua_close(state);
}

//binds the classes and methods
void Lua::bind_all()
{
	using namespace luaponte;

	//bind the resource manager methods
	module(state)
	[
		class_<AnimationResource>("AnimationResource"),
		class_<ImageResource>("ImageResource"),
		class_<FontResource>("FontResource"),

		class_<ResourceManager>("Resources")
		.def("LoadAnimation", &ResourceManager::load_resource<AnimationResource>)
		.def("LoadImage", &ResourceManager::load_resource<ImageResource>)
		.def("LoadFont", &ResourceManager::load_resource<FontResource>)
		.scope[def("GetInstance", &ResourceManager::get_instance)]
	];

	//bind the position component
	module(state)
	[
		class_<Position>("Position")
		.def("SetX", &Position::set_x)
		.def("SetY", &Position::set_y)
		.def("GetX", &Position::get_x)
		.def("GetY", &Position::get_y)
	];

	//bind the animation component
	module(state)
	[
		class_<Animation>("Animation")
		.def("AddState", (bool(Animation::*) (const std::string&, const std::string&)) &Animation::add_state)
		.def("AddState", (bool(Animation::*) (const std::string&, const std::shared_ptr<AnimationResource>&)) &Animation::add_state)
		.def("SetState", &Animation::set_state)
		.def("GetState", &Animation::get_state)
		.def("SetSpeed", &Animation::set_speed)
		.def("GetSpeed", &Animation::get_speed)
		.def("SetLayer", &Animation::set_layer)
		.def("GetLayer", &Animation::get_layer)
		.def("SetPosition", (void(Animation::*) (const std::shared_ptr<Position>&)) &Animation::set_position)
		.def("SetPosition", (void(Animation::*) (const std::string&)) &Animation::set_position)
		.def("UnsetPosition", &Animation::unset_position)
	];

	//bind the image component
	module(state)
	[
		class_<Image>("Image")
		.def("SetResource", (void(Image::*) (const std::shared_ptr<ImageResource>&)) &Image::set_resource)
		.def("SetResource", (void(Image::*) (const std::string&)) &Image::set_resource)
		.def("SetLayer", &Image::set_layer)
		.def("GetLayer", &Image::get_layer)
		.def("SetPosition", (void(Image::*) (const std::shared_ptr<Position>&)) &Image::set_position)
		.def("SetPosition", (void(Image::*) (const std::string&)) &Image::set_position)
		.def("UnsetPosition", &Image::unset_position)
	];

	//bind the text component
	module(state)
	[
		class_<Text>("Text")
		.def("SetResource", (void(Text::*) (const std::shared_ptr<FontResource>&)) &Text::set_resource)
		.def("SetResource", (void(Text::*) (const std::string&)) &Text::set_resource)
		.def("SetLayer", &Text::set_layer)
		.def("GetLayer", &Text::get_layer)
		.def("SetText", &Text::set_text)
		.def("GetText", &Text::get_text)
		.def("SetColor", (void(Text::*) (int)) &Text::set_color)
		.def("GetColor", &Text::get_color)
		.def("SetPosition", (void(Text::*) (const std::shared_ptr<Position>&)) &Text::set_position)
		.def("SetPosition", (void(Text::*) (const std::string&)) &Text::set_position)
		.def("UnsetPosition", &Text::unset_position)
	];

	//bind the component manager
	module(state)
	[
		class_<ComponentManager>("Components")
		.def("CreateAnimation", &ComponentManager::create_component<Animation>)
		.def("CreateImage", &ComponentManager::create_component<Image>)
		.def("CreateText", &ComponentManager::create_component<Text>)
		.def("CreatePosition", &ComponentManager::create_component<Position>)
		.scope[def("GetInstance", &ComponentManager::get_instance)]
	];
}
