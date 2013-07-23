#ifndef _SCRIPT_H_
#define _SCRIPT_H_

#include <luaponte\luaponte.hpp>
#include <luaponte\object.hpp>

#include "../../BaseObject.h"
#include "../BaseComponent.h"
#include "../../GameObject/GameObject.h"

class GameObject;

class Script : public BaseComponent, public BaseObject{
public:
	//component update function
	void update();

	Script(const std::string& name, GameObject& _go, const luaponte::object&);
	~Script() = default;
	Script() = delete;
	Script(const Script&) = delete;
	Script& operator=(const Script&) = delete;

private:
	luaponte::object script;
	GameObject& go;
};

#endif