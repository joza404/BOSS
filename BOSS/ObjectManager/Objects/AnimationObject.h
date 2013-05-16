#ifndef _ANIMATION_OBJECT_H_
#define _ANIMATION_OBJECT_H_

#define DEFAULT_STATE_NAME "main"

#include "Object.h"
#include <map>
#include <string>

class AnimationObject : public Object{
public:
	//у анимационного объекта есть разные "состояния" (например - полет влево\вправо)
	struct State{
		AnimationResource* res;
		std::string u_name;
	};

	//ширина и высота рисука выводимой части
	unsigned int w, h;
	//координаты объекта на экране
	unsigned int x,y;

	//текущий фрейм анимации (для рендера и логики)
	unsigned int curAnimFrame;
	//смещение
	unsigned int x_offset;
	//сколько нужно еще подождать фреймов, чтобы переключить фрейм анимации (для рендера)
	unsigned int frameWait;

	//создает новое состояние
	bool create_state(Resource* res, std::string u_name);
	//устанавливает новое состояние
	bool set_new_state(std::string u_name);
	//возвращает текущее состояние
	State* get_current_state();

private:
	//позволяем менеджеру управлять объектами
	friend ObjectManager;

	//map всех состояний
	std::map<std::string, State*> stateMap;
	//имя текущего состояния
	std::string curStateName;

	//создает объект
	bool create(Resource* res);
	//этот метод вызывает менеджер объектов перед уничтожением объекта
	bool destroy();

	AnimationObject() {};
	~AnimationObject() {};
	AnimationObject(const AnimationObject&) {};
	AnimationObject& operator=(const AnimationObject&) {};
};

//короткое название
typedef AnimationObject AO;

#endif