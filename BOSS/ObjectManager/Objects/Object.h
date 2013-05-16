#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "../../ResourceManager/ResourceList.h"

class ObjectManager;

enum ObjectType{
	ANIMATION_OBJECT,
	TEXT_OBJECT,
	IMAGE_OBJECT
};

class Object{
public:
	//уникальные идентификаторы объекта
	unsigned int u_id;
	std::string u_name;

	//тип объекта
	ObjectType type;

	//создает объект
	virtual bool create(Resource* res) = 0;
	//этот метод вызывает менеджер объектов перед уничтожением объекта
	virtual bool destroy() = 0;
};

#endif