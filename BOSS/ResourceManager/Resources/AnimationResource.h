#ifndef _ANIMATION_RESOURCE_H_
#define __ANIMATION_RESOURCE_H_

#include <SDL.h>
#include "Resource.h"

class AnimationResource : public Resource{
public:
	SDL_Surface* image;
	unsigned int frequency;
	unsigned int frameCount;
	int transColor;

private:
	//позволяем менеджеру управлять ресурсами
	friend ResourceManager;

	//загружает ресурс
	bool load(std::string path);
	//этот метод вызывает менеджер ресурсов перед уничтожением ресурса
	bool unload();

	AnimationResource() {frequency = frameCount = 0;};
	~AnimationResource() {};
	AnimationResource(const AnimationResource&) {};
	AnimationResource& operator=(const AnimationResource&) {};
};

typedef AnimationResource AR;

#endif