#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <string>
#include <memory>

#include "../Components/Animation/Animation.h"
#include "../Components/Image/Image.h"
#include "../Components/Text/Text.h"
#include "../Components/Position/Position.h"
#include "../Components/Movement/Movement.h"
#include "../Components/FSM/FSM.h"
#include "../Components/Script/Script.h"

class FSM;
class Script;

class GameObject{
public:
	//type name, it's like "OrcWarrior"
	const std::string typeName;
	//object name, it's like "OrcWarrior1", "OrcWarrior2"
	const std::string objectName;

	//all kind of components. we're not using smart ptr cuz of the bugs in Lua
	Animation* animation = nullptr;
	Image* image = nullptr;
	Text* text = nullptr;
	Position* position =  nullptr;
	Movement* movement = nullptr;
	FSM* fsm = nullptr;
	Script* script = nullptr;


	//check functions
	bool animation_exists() { return animation != nullptr; }
	bool image_exists() { return image != nullptr; }
	bool text_exists() { return text != nullptr; }
	bool position_exists() { return position != nullptr; }
	bool movement_exists() { return movement != nullptr; }
	bool fsm_exists() { return fsm != nullptr; }
	bool script_exists() { return script != nullptr; }

	GameObject(const std::string&, const std::string&);
	GameObject(GameObject&&);
	
	GameObject() = delete;
	GameObject(const GameObject&) = delete;
	GameObject& operator=(const GameObject&) = delete;
	~GameObject() = default;
};

typedef GameObject GO;

#endif