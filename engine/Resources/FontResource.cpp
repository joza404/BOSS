#include <fstream>
#include <iostream>
#include <stdexcept>

#include <SDL_ttf.h>

#include "FontResource.h"

FontResource::FontResource(const std::string& _name, const std::string& path) 
	: BaseObject(_name)
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

FontResource::FontResource(FontResource&& fr) : BaseObject( std::move(static_cast<BaseObject&>(fr)) )
{
	font = fr.font;
	fr.font = nullptr;
	size = fr.size;
}

FontResource::~FontResource()
{
	if (font != nullptr) TTF_CloseFont(this->font);
}