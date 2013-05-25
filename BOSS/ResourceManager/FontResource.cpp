#include "FontResource.h"
#include <SDL_ttf.h>
#include <fstream>
#include <iostream>

FontResource::FontResource(const std::string path, const std::string _name, const unsigned int _id) 
	: BaseObject(_name, _id), font(nullptr)
{
	std::ifstream file;
	std::string buffer;
	file.exceptions(std::istream::failbit | std::istream::badbit);
	try{
		file.open(path);

		//read the title
		file >> buffer;
		if (buffer != "FONT"){
			throw std::runtime_error("Error. The INFO file is not valid.");
		}

		//read the parameters
		file >> size;

		//read the font path
		file >> buffer;
		font = TTF_OpenFont(buffer.c_str(), size);
		if (font == nullptr){
			throw std::runtime_error("Error. The TTF file is not valid.");
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

FontResource::~FontResource()
{
	TTF_CloseFont(this->font);
}