#ifndef _BASE_OBJECT_H_
#define _BASE_OBJECT_H_

#include <string>

class BaseObject{
public:
	const std::string name;
	const unsigned int id;

	BaseObject(const std::string& _name, const unsigned int _id) 
		: name(_name), id(_id) {};
	virtual ~BaseObject() = 0;

private:
	BaseObject();
	BaseObject(const BaseObject&);
	BaseObject& operator=(const BaseObject&);
};
//pure virtual destructor
inline BaseObject::~BaseObject() {};

#endif