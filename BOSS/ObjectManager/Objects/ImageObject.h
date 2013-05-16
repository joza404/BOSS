#ifndef _IMAGE_OBJECT_H_
#define _IMAGE_OBJECT_H_

#include "Object.h"

class ImageObject : public Object{
public:
	//указатель на ресурс рисунка
	ImageResource* res;

	//смещение внутри рисунка
	unsigned int x_offset, y_offset;
	//ширина и высота рисука выводимой части
	unsigned int w, h;
	//координаты объекта на экране
	unsigned int x,y;

private:
	//позволяем менеджеру управлять объектами
	friend ObjectManager;

	//создает объект
	bool create(Resource* res);
	//этот метод вызывает менеджер объектов перед уничтожением объекта
	bool destroy();

	ImageObject() {};
	~ImageObject() {};
	ImageObject(const ImageObject&) {};
	ImageObject& operator=(const ImageObject&) {};
};

typedef ImageObject IO;

#endif