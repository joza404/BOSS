#ifndef _IMAGE_RESOURCE_H_
#define _IMAGE_RESOURCE_H_

#include <string>
#include <SDL.h>

#include "..\BaseObject.h"

class ImageResource : public BaseObject{
public:
	SDL_Surface* image;

	ImageResource(const std::string& path, const std::string& name, const unsigned int id);
	~ImageResource();

	ImageResource() = delete;
	ImageResource(const ImageResource&) = delete;
	ImageResource& operator=(const ImageResource&) = delete;
};

typedef ImageResource IR;
#endif