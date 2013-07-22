#ifndef _RIGID_BODY_RESOURCE_H_
#define _RIGID_BODY_RESOURCE_H_

#include <string>
#include <list>
#include <memory>
#include <list>

#include "../BaseObject.h"

class Square{
public:
	const std::string name;
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

	Square(const std::string&);
	Square(Square&& sq);

	Square() = delete;
	Square(const Square&) = delete;
	Square& operator=(const Square&) = delete;
	~Square() = default;
};

typedef std::list<Square> SquareList;

class RigidBodyResource : public BaseObject{
public:	
	std::list<SquareList> frameList;
	int frameNumber;

	RigidBodyResource(const std::string& name, const std::string& path);
	RigidBodyResource(RigidBodyResource&&);

	RigidBodyResource() = delete;
	RigidBodyResource(const RigidBodyResource&) = delete;
	RigidBodyResource& operator=(const RigidBodyResource&) = delete;
	~RigidBodyResource() = default;
};

typedef RigidBodyResource RBR;

#endif