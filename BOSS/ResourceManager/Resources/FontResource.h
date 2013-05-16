#ifndef _FONT_RESOURCE_H_
#define _FONT_RESOURCE_H_

#define DEFAULT_FONT_SIZE 10

#include <SDL.h>
#include <SDL_ttf.h>
#include "Resource.h"

class FontResource : public Resource{
public:
	//шрифт
	TTF_Font* font;

	//возвращает размер шрифта
	unsigned int get_size();
	//устанавливает новый размер шрифта(!ресурс будет перезагружен!)
	bool set_size(unsigned int size);

private:
	//позволяем менеджеру управлять ресурсами
	friend ResourceManager;

	//размер шрифта
	unsigned int size;
	//путь к файлу шрифтов
	std::string path;

	//загружает ресурс из файла, с произвольным размером
	bool load_font(int newSize = -1);

	//загружает ресурс из файла с размером, указанным в файле
	bool load(std::string path);
	//этот метод вызывает менеджер ресурсов перед уничтожением ресурса
	bool unload();

	FontResource() {};
	~FontResource() {};
	FontResource(const FontResource&) {};
	FontResource& operator=(const FontResource&) {};
};

typedef FontResource FR;

#endif