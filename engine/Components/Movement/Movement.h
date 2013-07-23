#ifndef _MOVEMENT_H_
#define _MOVEMENT_H_

#include <memory>
#include <map>
#include <string>

#include "../../BaseObject.h"
#include "../BaseComponent.h"
#include "../Position/Position.h"
#include "../Animation/Animation.h"

class Movement : public BaseComponent, public BaseObject{
public:
	void update();

	//set the velocity directly
	void set_velocity(int, int);

	//allows you to bind xVel and yVel to the certain name
	void add_state(const std::string& stateName, int, int);
	void set_state(const std::string& stateName);
	std::string get_state() { return currentState; }

	//switches the animation states depending on current movement state
	void set_animation(Animation* anim) { animationComp = anim; }
	void bind_animation_state(const std::string& stateName, const std::string& animationStateName);

	//set references to other components
	void set_position(Position* pos) { positionComp = pos; }
	void set_position(const std::string& pos);
	void unset_position() { positionComp = nullptr; }

	Movement(const std::string& name);
	~Movement() = default;
	Movement() = delete;
	Movement(const Movement&) = delete;
	Movement& operator=(const Movement&) = delete;

private:
	struct Velocity{
		int x = 0, y = 0;

		Velocity (int _x, int _y) : x(_x), y(_y) {}
		Velocity () {}
	} vel;

	std::string currentState;
	bool stateChanged = false;

	//key - movement state name, value - dependent velocity
	std::map<std::string, Velocity> velocityMap;

	//key - movement state name, value - animation state name
	std::map<std::string, std::string> animationMap;

	//references to other components
	Position* positionComp = nullptr;
	Animation* animationComp = nullptr;
};

#endif