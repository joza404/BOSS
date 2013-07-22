#include <fstream>
#include <iostream>
#include <stdexcept>

#include <SDL_image.h>
#include <SDL.h>

#include "ImageResource.h"
#include "../BaseObject.h"
#include "../Renderer/Renderer.h"

ImageResource::ImageResource(const std::string& _name, const std::string& path)
	: BaseObject(_name)
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
	
	Renderer::get_instance().convert_format(*this);
}

ImageResource::ImageResource(ImageResource&& ir) : BaseObject( std::move(static_cast<BaseObject&>(ir)) )
{
	image = ir.image;
	ir.image = nullptr;
}

ImageResource::~ImageResource()
{
	if (image != nullptr) SDL_FreeSurface(image);
}