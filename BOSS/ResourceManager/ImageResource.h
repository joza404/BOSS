#ifndef _IMAGE_RESOURCE_H_
#define _IMAGE_RESOURCE_H_

#include <SDL.h>
#include <string>
#include "..\BaseObject.h"

class ImageResource : public BaseObject{
public:
	SDL_Surface* image;

	ImageResource(const std::string path, const std::string name, const unsigned int id);
	~ImageResource();

private:
	ImageResource();
	ImageResource(const ImageResource&);
	ImageResource& operator=(const ImageResource&);
};

typedef ImageResource IR;
#endif