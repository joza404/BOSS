#include <fstream>
#include <iostream>
#include <stdexcept>

#include <SDL_image.h>
#include <SDL.h>

#include "ImageResource.h"
#include "../BaseObject.h"
#include "../Renderer/Renderer.h"

ImageResource::ImageResource(const std::string& path, const std::string& _name, const unsigned int _id)
	: BaseObject(_name, _id), image(nullptr)
{
	std::ifstream file;
	std::string buffer;
	file.exceptions(std::istream::failbit | std::istream::badbit);
	try{
		file.open(path);

		//read the title
		file >> buffer;
		if (buffer != "IMAGE"){
			throw std::runtime_error("Error. The INFO format is not valid.");
		}

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
	
	Renderer::get_instance()->convert_format(this);
}

ImageResource::~ImageResource()
{
	SDL_FreeSurface(image);
}