#ifndef _BASE_OBJECT_H_
#define _BASE_OBJECT_H_

#include <string>

class BaseObject{
public:
	const std::string name;
	const unsigned int id;

	BaseObject(const std::string& _name, const unsigned int _id) 
		: name(_name), id(_id) {}
	virtual ~BaseObject() = 0;

	BaseObject() = delete;
	BaseObject(const BaseObject&) = delete;
	BaseObject& operator=(const BaseObject&) = delete;
};
//pure virtual destructor
inline BaseObject::~BaseObject() = default;

#endif