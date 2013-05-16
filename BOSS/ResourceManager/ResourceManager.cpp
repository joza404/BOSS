#include "ResourceManager.h"
#include "ResourceList.h"
#include <iostream>
#include <fstream>

//начальное значение u_id
unsigned int RM::u_id = 0;

//создает единственный экземпляр класса
RM* RM::create_manager()
{
	static RM singleView;

#ifdef _DEBUG
	std::cout << "Менеджер ресурсов создан." << std::endl;
#endif

	return &singleView;
}

//загружает ресурс из файла и дает ему уникальное имя u_name
Resource* RM::load_resource(std::string path, std::string u_name)
{

	std::ifstream file(path);
	if (file.good() == false){
#ifdef _DEBUG
		std::cout << "Ошибка. Файл с именем " << path << " не найден, либо файл пуст, либо доступ запрещен" << std::endl;
#endif
		file.close();
		return 0;
	}

	//открыли файл, дальше используем исключения
	file.exceptions(std::istream::failbit | std::istream::badbit);
	std::string buff;
	try{
		file >> buff;
	}
	catch (...){
#ifdef _DEBUG
		std::cout << "Ошибка. Некорректный формат info файла ресурса: " << path << std::endl;
#endif
		file.close();
		return 0;
	}
	file.close();

	Resource* res;

	if (buff == "IMAGE"){
		res = new ImageResource();
		res->type = ResourceType::IMAGE_RESOURCE;
	} else 
	if (buff == "ANIMATION"){
		res = new AnimationResource();
		res->type = ResourceType::ANIMATION_RESOURCE;
	} else 
	if (buff == "FONT"){
		res = new FontResource();
		res->type = ResourceType::FONT_RESOURCE;
	} else {
#ifdef _DEBUG
		std::cout << "Ошибка. Неверный формат info файла ресурса: " << path << std::endl;
#endif
		return 0;
	}

	if (res->load(path) == false){
		//если возникла ошибка
		delete res;
		return 0;
	}

	//устанавливаем имя
	if (u_name != "_set_my_name_to_default_lol_")
		res->u_name = u_name;
	else 
		res->u_name = "_default_" + std::to_string(this->u_id) + "_";

	//устанавливаем id
	res->u_id = get_next_uid();

	//заполняем map'ы
	this->nameMap[res->u_name] = res;
	this->idMap[res->u_id] = res;

	return res;
}

//выгружает ресурс с именем u_name из памяти
bool RM::unload_resource(std::string u_name)
{
	try{
		//если не найден - вбросит исключение
		Resource* res = nameMap.at(u_name); 
		//удаляем из map'ов
		nameMap.erase(res->u_name);
		idMap.erase(res->u_id);

		res->unload();
		delete res;

		return true;
	}
	catch (...){
#ifdef _DEBUG
		std::cout << "Ошибка. Не найден ресурс с именем " << u_name << std::endl;
#endif
		return false;
	}
}

//выгружает ресурс с id == u_id из памяти
bool RM::unload_resource(unsigned int u_id)
{
	try{
		//если не найден - вбросит исключение
		Resource* res = idMap.at(u_id); 
		//удаляем из map'ов
		nameMap.erase(res->u_name);
		idMap.erase(res->u_id);

		res->unload();
		delete res;

		return true;
	}
	catch (...){
#ifdef _DEBUG
		std::cout << "Ошибка. Не найден ресурс с id = " << u_id << std::endl;
#endif
		return false;
	}
}

//выгружает ресурс res из памяти
bool RM::unload_resource(Resource* res)
{
	if (res == 0)
		return false;

	nameMap.erase(res->u_name);
	idMap.erase(res->u_id);

	res->unload();
	delete res;

	return true;
}

//Возвращает указатель на ресурс с именем u_name
Resource* RM::get_resource(std::string u_name)
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
Resource* RM::get_resource(unsigned int u_id)
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

ResourceManager::~ResourceManager()
{
	typedef std::map<unsigned int, Resource*>::iterator MI;
	//освобождаем ресурсы(но не очищаем map'ы, они сами будет освобождены)
	for(MI i = idMap.begin(); i != idMap.end(); i++)
		i->second->unload();

#ifdef _DEBUG
	std::cout << "Менеджер ресурсов уничтожен." << std::endl;
#endif
}