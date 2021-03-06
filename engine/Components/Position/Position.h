#ifndef _POSITION_H_
#define _POSITION_H_

#include "../../BaseObject.h"
#include "../BaseComponent.h"

class Position : public BaseComponent, public BaseObject{
public:
	void update();

	int get_x() const { return x; }
	int get_y() const { return y; }

	void set_x(int _x) { x = _x; }
	void set_y(int _y) { y = _y; }

	void add_x(int _x) { x += _x; }
	void add_y(int _y) { y += _y; }

	Position(const std::string& name);
	~Position() = default;
	Position() = delete;
	Position(const Position&) = delete;
	Position& operator=(const Position&) = delete;

private:
	int x, y;
};

#endif