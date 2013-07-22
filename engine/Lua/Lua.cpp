#include <memory>

#include <Lua.hpp>
#include <luaponte\luaponte.hpp>

#include "Lua.h"

#include "../Input/Input.h"

#include "../GameObject/GameObject.h"
#include "../GameObject/GameObjectManager.h"

#include "../Resources/ResourceManager.h"
#include "../Resources/AnimationResource.h"
#include "../Resources/ImageResource.h"
#include "../Resources/FontResource.h"

#include "../Components/ComponentManager.h"
#include "../Components/Animation/Animation.h"
#include "../Components/Image/Image.h"
#include "../Components/Position/Position.h"
#include "../Components/Text/Text.h"
#include "../Components/Movement.h"

//executes a script
bool Lua::do_file(const std::string& path)
{
	if (this->state == nullptr)
		return false;

	luaL_dofile(this->state,path.c_str());

	return true;
}

Lua::Lua()
{
	//init lua and luaponte
	state = luaL_newstate();
    luaL_openlibs(state);
	luaponte::open(state);
}

Lua::~Lua()
{
	lua_close(state);
}

//binds the classes and methods
void Lua::bind_all()
{
	using namespace luaponte;

	//bind the input global functions
	module(state)
	[
		def("register_key", &bind_register_key),
		def("key_pressed", &bind_key_pressed)
	];

	//bind game object
	module(state)
	[
		class_<GameObject>("GameObject")
		.def_readonly("typeName", &GameObject::typeName)
		.def_readonly("objectName", &GameObject::objectName)
		.def_readwrite("animation", &GameObject::animation)
		.def_readwrite("image", &GameObject::image)
		.def_readwrite("text", &GameObject::text)
		.def_readwrite("position", &GameObject::position)
		.def_readwrite("movement", &GameObject::movement)
		.def("AnimationExists", &GameObject::animation_exists)
		.def("ImageExists", &GameObject::image_exists)
		.def("TextExists", &GameObject::text_exists)
		.def("PositionExists", &GameObject::position_exists)
		.def("MovementExists", &GameObject::movement_exists)
	];

	//bind game object manager
	module(state)
	[
		class_<GameObjectManager>("GameObjectManager")
		.scope[def("GetInstance", &GameObjectManager::get_instance)]
		.def("CreateObjectType", &GameObjectManager::create_object_type)
		.def("CreateObject", &GameObjectManager::create_object)
		.def("GetObject", &GameObjectManager::get_object)
		.def("DeleteObject", (bool(GameObjectManager::*) (const std::string&, const std::string&)) &GameObjectManager::delete_object)
		.def("DeleteObject", (bool(GameObjectManager::*) (GameObject&)) &GameObjectManager::delete_object)
		.def("GlobalGetNext", &GameObjectManager::global_get_next)
		.def("GlobalReset", &GameObjectManager::global_reset)
		.def("GlobalEndReached", &GameObjectManager::global_end_reached)
		.def("GlobalGetSize", &GameObjectManager::global_get_size)
		.def("GetNext", &GameObjectManager::get_next)
		.def("Reset", &GameObjectManager::reset)
		.def("EndReached", &GameObjectManager::end_reached)
		.def("GetSize", &GameObjectManager::get_size)
	];

	//bind the resource manager
	module(state)
	[
		class_<AnimationResource>("AnimationResource"),
		class_<ImageResource>("ImageResource"),
		class_<FontResource>("FontResource"),
		class_<RigidBodyResource>("RigidBodyResource"),

		class_<ResourceManager>("ResourceManager")
		.def("LoadAnimationResource", &ResourceManager::load_animation_res)
		.def("LoadImageResource", &ResourceManager::load_image_res)
		.def("LoadFontResource", &ResourceManager::load_font_res)
		.def("LoadRigidBodyResource", &ResourceManager::load_rigidbody_res)
		.def("GetAnimationResource", &ResourceManager::get_animation_res)
		.def("GetImageResource", &ResourceManager::get_image_res)
		.def("GetFontResource", &ResourceManager::get_font_res)
		.def("GetRigidBodyResource", &ResourceManager::get_rigidbody_res)		
		.scope[def("GetInstance", &ResourceManager::get_instance)]
	];

	//bind the component manager
	module(state)
	[
		class_<ComponentManager>("ComponentManager")
		.def("CreateAnimationComponent", &ComponentManager::create_animation_comp)
		.def("CreateImageComponent", &ComponentManager::create_image_comp)
		.def("CreateTextComponent", &ComponentManager::create_text_comp)
		.def("CreatePositionComponent", &ComponentManager::create_position_comp)
		.def("GetAnimationComponent", &ComponentManager::get_animation_comp)
		.def("GetImageComponent", &ComponentManager::get_image_comp)
		.def("GetTextComponent", &ComponentManager::get_text_comp)
		.def("GetPositionComponent", &ComponentManager::get_position_comp)
		.def("DestroyAnimationComponent", (void(ComponentManager::*) (const std::string&)) &ComponentManager::delete_animation_comp)
		.def("DestroyImageComponent", (void(ComponentManager::*) (const std::string&)) &ComponentManager::delete_image_comp)
		.def("DestroyTextComponent", (void(ComponentManager::*) (const std::string&)) &ComponentManager::delete_text_comp)
		.def("DestroyPositionComponent", (void(ComponentManager::*) (const std::string&)) &ComponentManager::delete_position_comp)
		.def("DestroyAnimationComponent", (void(ComponentManager::*) (Animation*)) &ComponentManager::delete_animation_comp)
		.def("DestroyImageComponent", (void(ComponentManager::*) (Image*)) &ComponentManager::delete_image_comp)
		.def("DestroyTextComponent", (void(ComponentManager::*) (Text*)) &ComponentManager::delete_text_comp)
		.def("DestroyPositionComponent", (void(ComponentManager::*) (Position*)) &ComponentManager::delete_position_comp)
		.scope[def("GetInstance", &ComponentManager::get_instance)]
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
		.def("AddState", (void(Animation::*) (const std::string&, const std::string&)) &Animation::add_state)
		.def("AddState", (void(Animation::*) (const std::string&, AnimationResource&)) &Animation::add_state)
		.def("SetState", &Animation::set_state)
		.def("GetState", &Animation::get_state)
		.def("SetSpeed", &Animation::set_speed)
		.def("GetSpeed", &Animation::get_speed)
		.def("SetLayer", &Animation::set_layer)
		.def("GetLayer", &Animation::get_layer)
		.def("SetPosition", (void(Animation::*) (Position*)) &Animation::set_position)
		.def("SetPosition", (void(Animation::*) (const std::string&)) &Animation::set_position)
		.def("UnsetPosition", &Animation::unset_position)
	];

	//bind the image component
	module(state)
	[
		class_<Image>("Image")
		.def("SetResource", (void(Image::*) (ImageResource&)) &Image::set_resource)
		.def("SetResource", (void(Image::*) (const std::string&)) &Image::set_resource)
		.def("SetLayer", &Image::set_layer)
		.def("GetLayer", &Image::get_layer)
		.def("SetPosition", (void(Image::*) (Position*)) &Image::set_position)
		.def("SetPosition", (void(Image::*) (const std::string&)) &Image::set_position)
		.def("UnsetPosition", &Image::unset_position)
	];

	//bind the text component
	module(state)
	[
		class_<Text>("Text")
		.def("SetResource", (void(Text::*) (FontResource&)) &Text::set_resource)
		.def("SetResource", (void(Text::*) (const std::string&)) &Text::set_resource)
		.def("SetLayer", &Text::set_layer)
		.def("GetLayer", &Text::get_layer)
		.def("SetText", &Text::set_text)
		.def("GetText", &Text::get_text)
		.def("SetColor", (void(Text::*) (int)) &Text::set_color)
		.def("GetColor", &Text::get_color)
		.def("SetPosition", (void(Text::*) (Position*)) &Text::set_position)
		.def("SetPosition", (void(Text::*) (const std::string&)) &Text::set_position)
		.def("UnsetPosition", &Text::unset_position)
	];

	//bind the movement component
	module(state)
	[
		class_<Movement>("Movement")
		.def("SetVelocity", &Movement::set_velocity)
		.def("SetPosition", (void(Text::*) (Position*)) &Movement::set_position)
		.def("SetPosition", (void(Text::*) (const std::string&)) &Movement::set_position)
		.def("UnsetPosition", &Movement::unset_position)
	];
}
