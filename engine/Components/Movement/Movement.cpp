#include "Movement.h"
#include "../ComponentManager.h"

//local macroses (in .cpp)
#define DEFAULT_X_VELOCITY 0
#define DEFAULT_Y_VELOCITY 0

void Movement::update()
{
	//if position component exists
	if (positionComp.expired() == false){
		auto shared = positionComp.lock();
		shared->set_x(shared->get_x() + xVel);
		shared->set_y(shared->get_y() + yVel);
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
	positionComp = ComponentManager::get_instance()->get_component<Position>(pos);
}

Movement::Movement(const std::string& _name, const unsigned int _id) : BaseObject(_name, _id)
{
	xVel = DEFAULT_X_VELOCITY;
	yVel = DEFAULT_Y_VELOCITY;
}