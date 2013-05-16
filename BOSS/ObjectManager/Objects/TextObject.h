#ifndef _TEXT_OBJECT_H
#define _TEXT_OBJECT_H

#define DEFAULT_TEXT "DEFAULT"
#define DEFAULT_COLOR 0x00FFFFFF

#include "Object.h"
#include <SDL.h>

class TextObject : public Object{
public:
	//указатель на ресурс шрифта
	FontResource* res;
	//где будет хранится surface текста
	SDL_Surface* image;

	//координаты объекта на экране
	unsigned int x,y;

	//устанавливает новый текст выводимой строки
	bool set_text(std::string text);
	//возвращает текст 
	std::string get_text();
	bool set_size(unsigned int size);
	unsigned int get_size();
	//устанавливает цвет текста в формате 0x00RRGGBB
	bool set_color(int color);
	//возвращает цвет
	int get_color();

private:
	//позволяем менеджеру управлять объектами
	friend ObjectManager;

	//текст
	std::string text;
	//цвет текста
	SDL_Color color;

	//создает изображение на основе font, text, color
	bool create_image();

	//создает объект
	bool create(Resource* res);
	//этот метод вызывает менеджер объектов перед уничтожением объекта
	bool destroy();

	TextObject() {};
	~TextObject() {};
	TextObject(const TextObject&) {};
	TextObject& operator=(const TextObject&) {};
};

//короткое название
typedef TextObject TO;

#endif