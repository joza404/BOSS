#ifndef _FSM_H_
#define _FSM_H_

#include <luaponte\luaponte.hpp>
#include <luaponte\object.hpp>

#include "../../BaseObject.h"
#include "../BaseComponent.h"
#include "../../GameObject/GameObject.h"

class GameObject;

class FSM : public BaseComponent, public BaseObject{
public:
	//component update function
	void update();

	//assigns a state to the FSM
	void set_current_state(const luaponte::object& s) {currentState = s;}

	//change to a new state
	void change_state(const luaponte::object& new_state);

	FSM(const std::string& name, GameObject& _go);
	~FSM() = default;
	FSM() = delete;
	FSM(const FSM&) = delete;
	FSM& operator=(const FSM&) = delete;

private:
	luaponte::object currentState;
	GameObject& go;
};

#endif