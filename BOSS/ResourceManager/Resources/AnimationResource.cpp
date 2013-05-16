#include <fstream>
#include <string>
#include <iostream>

#include "AnimationResource.h"
#include <SDL.h>
#include <SDL_image.h>

//загружает ресурс
bool AnimationResource::load(std::string path)
{
	std::ifstream file(path);
	if (file.good() == false){
#ifdef _DEBUG
		std::cout << "Ошибка. Файл с именем " << path << " не найден, либо файл пуст, либо доступ запрещен" << std::endl;
#endif
		file.close();
		return false;
	}

	file.exceptions(std::istream::failbit | std::istream::badbit);
	std::string buff;
	try{
		file >> buff;
		if (buff != "ANIMATION"){
	#ifdef _DEBUG
			std::cout << "Ошибка. Некорректный формат info файла ресурса: " << path << std::endl;
	#endif
			file.close();
			return false;
		}

		//загружаем изображение
		file >> buff;
		SDL_Surface* surface = IMG_Load(buff.c_str());
		if (surface == 0){
#ifdef _DEBUG
			std::cout << "Ошибка. Некорректный формат файла ресурса: " << buff << std::endl;
#endif
			file.close();
			return false;
		}

		//загружаем остальные значения
		file >> this->frequency;
		file >> this->frameCount;
		file >> std::hex >> this->transColor;
		
		//загрузка выполнена успешно
		this->image = surface;
		this->type = ResourceType::ANIMATION_RESOURCE;

#ifdef _DEBUG
		std::cout << "Ресурс " << buff << " загружен" << std::endl;
#endif

		file.close();
		return true;
	}
	catch (...) {
#ifdef _DEBUG
		std::cout << "Ошибка. Некорректный формат info файла ресурса: " << path << std::endl;
#endif
		file.close();
		return false;
	}

}

//этот метод вызывает менеджер ресурсов перед уничтожением ресурса
bool AnimationResource::unload()
{
	SDL_FreeSurface(this->image);

	return true;
}