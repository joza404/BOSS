#include "Position.h"

Position::Position(const std::string _name, const unsigned int _id) : BaseObject(_name, _id)
{
	x = DEFAULT_X_POSITION;
	y = DEFAULT_Y_POSITION;
}