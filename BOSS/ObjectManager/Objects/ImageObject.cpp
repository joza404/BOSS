#include <iostream>
#include "ImageObject.h"
#include "..\..\ResourceManager\ResourceList.h"

//создает объект
bool ImageObject::create(Resource* res)
{
	if (res == 0){
#ifdef _DEBUG
		std::cout << "Ошибка. Не удалось создать объект, отсутствует ресурс." << std::endl;
#endif
		return false;
	}

	ImageResource* ires = dynamic_cast<ImageResource*>(res);
	if (ires == 0){
#ifdef _DEBUG
		std::cout << "Ошибка. Не удалось создать объект, неверный тип ресурса." << std::endl;
#endif
		return false;
	}

	//инициализируем поля объекта
	this->res = ires;
	this->x_offset = 0;
	this->y_offset = 0;
	this->x = 0;
	this->y = 0;
	this->w = ires->image->w;
	this->h = ires->image->h;
	this->type = ObjectType::IMAGE_OBJECT;

	return true;
}

//этот метод вызывает менеджер объектов перед уничтожением объекта
bool ImageObject::destroy()
{
	//ничего не делаем, т.к. этот объект при создании не выделяет динамическую память
	return true;
}