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
	//���������� �������������� �������
	unsigned int u_id;
	std::string u_name;

	//��� �������
	ObjectType type;

	//������� ������
	virtual bool create(Resource* res) = 0;
	//���� ����� �������� �������� �������� ����� ������������ �������
	virtual bool destroy() = 0;
};

#endif