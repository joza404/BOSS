#ifndef _POSITION_H_
#define _POSITION_H_

#include "../../BaseObject.h"
#include "../BaseComponent.h"

class Position : public BaseComponent, public BaseObject{
public:
	void update();

	int get_x() const { return x; }
	void set_x(int _x) { x = _x; }
	int get_y() const { return y; }
	void set_y(int _y) { y = _y; }

	Position(const std::string& name, const unsigned int id);
	~Position() = default;
	Position() = delete;
	Position(const Position&) = delete;
	Position& operator=(const Position&) = delete;

private:
	int x, y;
};

#endif