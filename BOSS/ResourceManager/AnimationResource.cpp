#include "AnimationResource.h"
#include <SDL_image.h>
#include <SDL.h>
#include <fstream>
#include <iostream>

AnimationResource::AnimationResource(const std::string& path, const std::string& _name, const unsigned int _id) 
	: BaseObject(_name, _id), image(nullptr)
{
	std::ifstream file;
	std::string buffer;
	file.exceptions(std::istream::failbit | std::istream::badbit);
	try{
		file.open(path);

		//read the title
		file >> buffer;
		if (buffer != "ANIMATION"){
			throw std::runtime_error("Error. The INFO file is not valid.");
		}

		//read the parameters
		file >> spriteCount;
		file >> std::hex >> transColor;

		//read the image path
		file >> buffer;
		image = IMG_Load(buffer.c_str());
		if (image == nullptr){
			throw std::runtime_error("Error. The image format is not valid.");
		}

		#ifdef _DEBUG
			std::cout << "The resource " << buffer << " has been loaded." << std::endl;
		#endif
		file.close();
	}
	catch (...) {
		#ifdef _DEBUG
			std::cout << "Error. The resource hasn't been loaded. " << path << std::endl;
		#endif
		file.close();
		throw;
	}
}

AnimationResource::~AnimationResource()
{
	SDL_FreeSurface(image);
}