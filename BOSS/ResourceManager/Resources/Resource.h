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
	//уникальные идентификаторы ресурса
	int u_id;
	std::string u_name;

	//тип ресурса
	ResourceType type;

	//загружает ресурс
	virtual bool load(std::string path) = 0;
	//этот метод вызывает менеджер ресурсов перед уничтожением ресурса
	virtual bool unload() = 0;
};

#endif