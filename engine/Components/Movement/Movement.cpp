#include "Movement.h"
#include "../ComponentManager.h"

//local macroses (in .cpp)
#define DEFAULT_X_VELOCITY 0
#define DEFAULT_Y_VELOCITY 0

void Movement::update()
{
	if (stateChanged == true){
		//set new velocity
		Velocity tempVel = velocityMap[currentState];
		vel.x = tempVel.x;
		vel.y = tempVel.y;

		//set new animation state
		auto it = animationMap.find(currentState);
		if (it != animationMap.end()){
			//got it
			animationComp->set_state(it->second);
		}

		stateChanged = false;
	}

	//if position component exists
	if (positionComp != nullptr){
		positionComp->add_x(vel.x);
		positionComp->add_y(vel.y);
	}
}

void Movement::set_velocity(int xVel, int yVel)
{
	vel.x = xVel;
	vel.y = yVel;
}

//allows you to bind xVel and yVel to the certain name
void Movement::add_state(const std::string& stateName, int xVel, int yVel)
{
	velocityMap.insert( std::make_pair(stateName, Velocity(xVel, yVel)) );
}
void Movement::set_state(const std::string& stateName)
{
	currentState = stateName;
	stateChanged = true;
}

void Movement::bind_animation_state(const std::string& stateName, const std::string& animationStateName)
{
	if (animationComp == nullptr) return;
	animationMap.insert( std::make_pair(stateName, animationStateName) );
}

//set references to other components
void Movement::set_position(const std::string& pos)
{
	positionComp = ComponentManager::get_instance().get_position_comp(pos);
}

Movement::Movement(const std::string& _name) : BaseObject(_name)
{
	vel.x = DEFAULT_X_VELOCITY;
	vel.y = DEFAULT_Y_VELOCITY;
}