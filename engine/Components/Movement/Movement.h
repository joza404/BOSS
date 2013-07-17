#ifndef _MOVEMENT_H_
#define _MOVEMENT_H_

#include <memory>
#include "../../BaseObject.h"
#include "../BaseComponent.h"
#include "../Position/Position.h"

class Movement : public BaseComponent, public BaseObject{
public:
	void update();

	void set_velocity(int, int);

	//set references to other components
	void set_position(const std::shared_ptr<Position>& pos) { positionComp = pos; }
	void set_position(const std::string& pos);
	void unset_position() { positionComp.reset(); }

	Movement(const std::string& name, const unsigned int id);
	~Movement() = default;
	Movement() = delete;
	Movement(const Movement&) = delete;
	Movement& operator=(const Movement&) = delete;

private:
	int xVel, yVel;

	//references to other components
	std::weak_ptr<Position> positionComp;
};

#endif