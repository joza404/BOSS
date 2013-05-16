#include <fstream>
#include <string>
#include <iostream>

#include "FontResource.h"
#include <SDL.h>

//возвращает размер шрифта
unsigned int FontResource::get_size()
{
	return this->size;
}

//устанавливает новый размер шрифта(!ресурс будет перезагружен!)
bool FontResource::set_size(unsigned int size)
{
	//успешно загрузили ресурс
	if(this->load_font(size)){
		this->size = size;
		return true;
	}

	return false;
}

//загружает ресурс
bool FontResource::load(std::string path)
{
	this->font = 0;
	this->path = path;

	//загружаем ресурс с размером -1, что значит "возьми из файла"
	return this->load_font();
}

bool FontResource::load_font(int newSize)
{
	std::ifstream file(path);
	if (file.good() == false){
#ifdef _DEBUG
		std::cout << "Ошибка. Файл с именем " << path << " не найден, либо файл пуст, либо доступ запрещен" << std::endl;
#endif
		file.close();
		return false;
	}

	//открыли файл, дальше используем исключения
	file.exceptions(std::istream::failbit | std::istream::badbit);
	std::string buff;
	try{
		file >> buff;
		if (buff != "FONT"){
#ifdef _DEBUG
			std::cout << "Ошибка. Некорректный формат info файла ресурса: " << path << std::endl;
#endif
			file.close();
			return false;
		}
	
		//путь к файлу шрифта
		file >> buff;

		if (newSize < 0){
			//берем размер из файла
			file >> this->size;
		} else {
			//пользователь передал размер
			this->size = newSize;
		}
		//загружаем шрифт
		TTF_Font* font = TTF_OpenFont(buff.c_str(), this->size);
		if (font == 0){
#ifdef _DEBUG
			std::cout << "Ошибка. Не удалось загрузить шрифт с именем: " << buff << std::endl;
#endif
			file.close();
			return false;
		}

		//проверяем загружали ли мы шрифт до этого
		if (this->font != 0)
			TTF_CloseFont(this->font);
		this->font = font;
		this->type = ResourceType::FONT_RESOURCE;

#ifdef _DEBUG
		std::cout << "Ресурс " << buff << " загружен" << std::endl;
#endif

		file.close();
		return true;
	}
	catch (...){
#ifdef _DEBUG
		std::cout << "Ошибка. Некорректный формат info файла ресурса: " << path << std::endl;
#endif
		file.close();
		return false;
	}
}

//этот метод вызывает менеджер ресурсов перед уничтожением ресурса
bool FontResource::unload()
{
	TTF_CloseFont(this->font);

	return true;
}