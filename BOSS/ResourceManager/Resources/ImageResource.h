#ifndef _IMAGE_RESOURCE_H_
#define _IMAGE_RESOURCE_H_

#include <SDL.h>
#include "Resource.h"

class ImageResource : public Resource{
public:
	SDL_Surface* image;

private:
	//позволяем менеджеру управлять ресурсами
	friend ResourceManager;

	//загружает ресурс
	bool load(std::string path);
	//этот метод вызывает менеджер ресурсов перед уничтожением ресурса
	bool unload();

	ImageResource() {};
	~ImageResource() {};
	ImageResource(const ImageResource&) {};
	ImageResource& operator=(const ImageResource&) {};
};

typedef ImageResource IR;

#endif