#ifndef _BASE_COMPONENT_H_
#define _BASE_COMPONENT_H_

class BaseComponent{
public:
	virtual void update() = 0;
	virtual ~BaseComponent() = 0;
};
//pure virtual destructor
inline BaseComponent::~BaseComponent() = default;

#endif