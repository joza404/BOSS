#ifndef _POSITION_H_
#define _POSITION_H_

#include "../../BaseObject.h"
#include "../BaseComponent.h"

#define DEFAULT_X_POSITION 100
#define DEFAULT_Y_POSITION 100

class Position : public BaseComponent, public BaseObject{
public:
	int get_x() { return x; }
	void set_x(int _x) { x = _x; }
	int get_y() { return y; }
	void set_y(int _y) { x = _y; }

	Position(const std::string name, const unsigned int id);
	~Position() {};
private:
	int x, y;

	Position();
	Position(const Position&);
	Position& operator=(const Position&);
};

#endif