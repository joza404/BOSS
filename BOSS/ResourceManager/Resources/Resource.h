#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include <string>

#include "..\ResourceManager.h"

class ResourceManager;

enum ResourceType{
	ANIMATION_RESOURCE,
	FONT_RESOURCE,
	IMAGE_RESOURCE
};

class Resource{
public:
	//���������� �������������� �������
	int u_id;
	std::string u_name;

	//��� �������
	ResourceType type;

	//��������� ������
	virtual bool load(std::string path) = 0;
	//���� ����� �������� �������� �������� ����� ������������ �������
	virtual bool unload() = 0;
};

#endif