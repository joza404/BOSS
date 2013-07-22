#ifndef _BASE_OBJECT_H_
#define _BASE_OBJECT_H_

#include <string>

class BaseObject{
public:
	const std::string name;

	BaseObject(const std::string& _name) 
		: name(_name) {}
	BaseObject(BaseObject&& bo) : name(std::move(bo.name)) {}
	virtual ~BaseObject() = 0;

	BaseObject() = delete;
	BaseObject(const BaseObject&) = delete;
	BaseObject& operator=(const BaseObject&) = delete;
};
//pure virtual destructor
inline BaseObject::~BaseObject() = default;

#endif