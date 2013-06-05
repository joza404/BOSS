#ifndef _ANIMATION_RESOURCE_H_
#define _ANIMATION_RESOURCE_H_

#include <SDL.h>
#include <string>

#include "../BaseObject.h"

class AnimationResource : public BaseObject{
public:	
	SDL_Surface* image;
	unsigned int spriteCount;
	int transColor;

	AnimationResource(const std::string& path, const std::string& name, const unsigned int id);
	~AnimationResource();

	AnimationResource() = delete;
	AnimationResource(const AnimationResource&) = delete;
	AnimationResource& operator=(const AnimationResource&) = delete;
};

typedef AnimationResource AR;
#endif