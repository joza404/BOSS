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

	AnimationResource(const std::string path, const std::string name, const unsigned int id);
	~AnimationResource();

private:
	AnimationResource();
	AnimationResource(const AnimationResource&);
	AnimationResource& operator=(const AnimationResource&);
};

typedef AnimationResource AR;
#endif