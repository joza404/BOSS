#include "Movement.h"
#include "../ComponentManager.h"

//local macroses (in .cpp)
#define DEFAULT_X_VELOCITY 0
#define DEFAULT_Y_VELOCITY 0

void Movement::update()
{
	//if position component exists
	if (positionComp != nullptr){
		positionComp->set_x(positionComp->get_x() + xVel);
		positionComp->set_y(positionComp->get_y() + yVel);
	}
}

void Movement::set_velocity(int _xVel, int _yVel)
{
	xVel = _xVel;
	yVel = _yVel;
}

//set references to other components
void Movement::set_position(const std::string& pos)
{
	positionComp = ComponentManager::get_instance().get_position_comp(pos);
}

Movement::Movement(const std::string& _name) : BaseObject(_name)
{
	xVel = DEFAULT_X_VELOCITY;
	yVel = DEFAULT_Y_VELOCITY;
}