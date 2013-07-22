#ifndef _ANIMATION_RESOURCE_H_
#define _ANIMATION_RESOURCE_H_

#include <SDL.h>
#include <string>

#include "../BaseObject.h"

class AnimationResource : public BaseObject{
public:	
	SDL_Surface* image = nullptr;
	unsigned int spriteNumber;
	int transColor;

	AnimationResource(const std::string& name, const std::string& path);
	AnimationResource(AnimationResource&&);
	~AnimationResource();

	AnimationResource() = delete;
	AnimationResource(const AnimationResource&) = delete;
	AnimationResource& operator=(const AnimationResource&) = delete;
};

typedef AnimationResource AR;
#endif