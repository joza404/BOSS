#include <iostream>
#include "ObjectManager.h"
#include "ObjectList.h"

//начальное значение u_id
unsigned int OM::u_id = 0;

//создает единственный экземпляр класса
OM* OM::create_manager()
{
	static OM singleView;

#ifdef _DEBUG
	std::cout << "Менеджер объектов создан." << std::endl;
#endif

	return &singleView;
}

Object* OM::create_object(Resource* res, std::string u_name)
{
	if (res == 0){
#ifdef _DEBUG
		std::cout << "Ошибка. Не удалось создать объект, отсутствует ресурс." << std::endl;
#endif
		return false;
	}

	Object* obj;
	//создаем объект типа image
	if (res->type == ResourceType::IMAGE_RESOURCE){
		obj = new ImageObject();
		obj->type = ObjectType::IMAGE_OBJECT;
	} else
	if (res->type == ResourceType::ANIMATION_RESOURCE){
		obj = new AnimationObject();
		obj->type = ObjectType::ANIMATION_OBJECT;
	} else
	if (res->type == ResourceType::FONT_RESOURCE){
		obj = new TextObject();
		obj->type = ObjectType::TEXT_OBJECT;
	} else {
		//сюда никогда не попадем по идее
		return 0;
	}

	//инициализируем объект
	if (obj->create(res) == false){
		//если возникла ошибка
		delete obj;
		return 0;
	}

	//устанавливаем имя
	if (u_name != "_set_my_name_to_default_lol_")
		obj->u_name = u_name;
	else 
		obj->u_name = "_default_" + std::to_string(this->u_id) + "_";

	//устанавливаем id
	obj->u_id = get_next_uid();

	//заполняем map'ы
	this->nameMap[obj->u_name] = obj;
	this->idMap[obj->u_id] = obj;

	return obj;
}

//выгружает объект с именем u_name из памяти
bool OM::destroy_object(std::string u_name)
{
	try{
		//если не найден - вбросит исключение
		Object* obj = nameMap.at(u_name); 
		//удаляем из map'ов
		nameMap.erase(obj->u_name);
		idMap.erase(obj->u_id);

		obj->destroy();
		delete obj;

		return true;
	}
	catch (...){
#ifdef _DEBUG
		std::cout << "Ошибка. Не найден объект с именем " << u_name << std::endl;
#endif
		return false;
	}
}

//выгружает ресурс с id == u_id из памяти
bool OM::destroy_object(unsigned int u_id)
{
	try{
		//если не найден - вбросит исключение
		Object* obj = idMap.at(u_id); 
		//удаляем из map'ов
		nameMap.erase(obj->u_name);
		idMap.erase(obj->u_id);

		obj->destroy();
		delete obj;

		return true;
	}
	catch (...){
#ifdef _DEBUG
		std::cout << "Ошибка. Не найден объект с id = " << u_id << std::endl;
#endif
		return false;
	}
}

//выгружает ресурс obj из памяти
bool OM::destroy_object(Object* obj)
{
	if (obj == 0)
		return false;

	nameMap.erase(obj->u_name);
	idMap.erase(obj->u_id);

	obj->destroy();
	delete obj;

	return true;
}

//Возвращает указатель на ресурс с именем u_name
Object* OM::get_object(std::string u_name)
{
	try{
		//если не найден - вбросит исключение
		return nameMap.at(u_name);
	}
	catch (...){
#ifdef _DEBUG
		std::cout << "Ошибка. Не найден ресурс с именем " << u_name << std::endl;
#endif
		return 0;
	}
}

//Возвращает указатель на ресурс с id == u_id
Object* OM::get_object(unsigned int u_id)
{
	try{
		//если не найден - вбросит исключение
		return idMap.at(u_id);
	}
	catch (...){
#ifdef _DEBUG
		std::cout << "Ошибка. Не найден ресурс с id = " << u_id << std::endl;
#endif
		return 0;
	}
}

ObjectManager::~ObjectManager()
{
	typedef std::map<unsigned int, Object*>::iterator MI;
	//освобождаем ресурсы(но не очищаем map'ы, они сами будет освобождены)
	for(MI i = idMap.begin(); i != idMap.end(); i++)
		i->second->destroy();

#ifdef _DEBUG
	std::cout << "Менеджер объектов уничтожен." << std::endl;
#endif
}