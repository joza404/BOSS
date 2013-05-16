#include <iostream>
#include "AnimationObject.h"

//создает новое состояние
bool AnimationObject::create_state(Resource* res, std::string u_name)
{
	if (res == 0){
#ifdef _DEBUG
		std::cout << "Ошибка. Нельзя создать новое состояние объекта без ресурса." << std::endl;
#endif
		return false;
	}

	AnimationResource* ares = dynamic_cast<AnimationResource*>(res);
	if (ares == 0){
#ifdef _DEBUG
		std::cout << "Ошибка. Не удалось создать состояние, неверный тип ресурса." << std::endl;
#endif
		return false;
	}

	State* st = new State();
	st->res = ares;
	st->u_name = u_name;
	
	//добавляем в map
	stateMap[u_name] = st;

	return true;
}

//устанавливает новое состояние
bool AnimationObject::set_new_state(std::string u_name)
{
	try{
		//если не найден - вбросит исключение
		State* newSt = stateMap.at(u_name);
		
		//изменяем текущий фрейм
		curStateName = u_name;
		//изменяем ширину и высоту объекта в соотв. с состоянием
		h = newSt->res->image->h;
		w = newSt->res->image->w / newSt->res->frameCount;
		//обработка с нового фрейма анимации
		curAnimFrame = 0;
		x_offset = 0;
		//ждем фреймов до нового фрейма анимации
		frameWait = newSt->res->frequency - 1;

		return true;
	}
	catch (...){
#ifdef _DEBUG
		std::cout << "Ошибка. Не найдено состояние с именем " << u_name << std::endl;
#endif
		return false;
	}
}

//возвращает текущее состояние
AnimationObject::State* AnimationObject::get_current_state()
{
	return stateMap[curStateName];
}

//создает объект
bool AnimationObject::create(Resource* res)
{
	if (res == 0){
#ifdef _DEBUG
		std::cout << "Ошибка. Не удалось создать объект, отсутствует ресурс." << std::endl;
#endif
		return false;
	}

	AnimationResource* ares = dynamic_cast<AnimationResource*>(res);
	if (ares == 0){
#ifdef _DEBUG
		std::cout << "Ошибка. Не удалось создать объект, неверный тип ресурса." << std::endl;
#endif
		return false;
	}

	//инициализируем поля объекта
	//создает первый State с именем "main"
	this->create_state(ares, DEFAULT_STATE_NAME);
	//устанавливаем текущий state на "main"
	this->set_new_state(DEFAULT_STATE_NAME);
	//инициализируем координаты
	this->x = 0;
	this->y = 0;
	this->type = ObjectType::ANIMATION_OBJECT;

	return true;
}

//этот метод вызывает менеджер объектов перед уничтожением объекта
bool AnimationObject::destroy()
{
	//удаляем все состояния
	typedef std::map<std::string, State*>::iterator MI;
	for(MI i = stateMap.begin(); i != stateMap.end(); i++)
		delete i->second;

	return true;
}