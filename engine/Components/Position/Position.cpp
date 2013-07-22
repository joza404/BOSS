#include "Position.h"

//local macroses (in .cpp)
#define DEFAULT_X_POSITION 100
#define DEFAULT_Y_POSITION 100

void Position::update()
{
}

Position::Position(const std::string& _name) : BaseObject(_name)
{
	x = DEFAULT_X_POSITION;
	y = DEFAULT_Y_POSITION;
}