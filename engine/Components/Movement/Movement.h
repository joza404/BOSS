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
	void set_position(Position* pos) { positionComp = pos; }
	void set_position(const std::string& pos);
	void unset_position() { positionComp = nullptr; }

	Movement(const std::string& name);
	~Movement() = default;
	Movement() = delete;
	Movement(const Movement&) = delete;
	Movement& operator=(const Movement&) = delete;

private:
	int xVel, yVel;

	//references to other components
	Position* positionComp;
};

#endif