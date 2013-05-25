#ifndef _FONT_RESOURCE_H_
#define _FONT_RESOURCE_H_

#include <string>
#include <SDL_ttf.h>
#include "..\BaseObject.h"

class FontResource : public BaseObject{
public:
	TTF_Font* font;
	unsigned int size;

	FontResource(const std::string path, const std::string name, const unsigned int id);
	~FontResource();

private:
	FontResource();
	FontResource(const FontResource&);
	FontResource& operator=(const FontResource&);
};

typedef FontResource FR;
#endif