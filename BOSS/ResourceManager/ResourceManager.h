#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_

#include <map>
#include <list>
#include <string>

#include "Resources\Resource.h"

class Resource;

class ResourceManager{
public:
	//создает единственный экземпляр класса
	static ResourceManager* create_manager();
	//загружает ресурс из файла и дает ему уникальное имя u_name
	Resource* load_resource(std::string path, std::string u_name = "_set_my_name_to_default_lol_");
	//выгружает ресурс с именем u_name из памяти
	bool unload_resource(std::string u_name);
	//выгружает ресурс с id == u_id из памяти
	bool unload_resource(unsigned int u_id);
	//выгружает ресурс res из памяти
	bool unload_resource(Resource* res);
	
	//Возвращает указатель на ресурс с именем u_name
	Resource* get_resource(std::string u_name);
	//Возвращает указатель на ресурс с id == u_id
	Resource* get_resource(unsigned int u_id);

private:
	//map для быстрого поиска по ключу, также хранит указатель на ресурс
	std::map<std::string, Resource*> nameMap;
	std::map<unsigned int, Resource*> idMap;

	//каждому новому ресурсу присваивается новый u_id
	static unsigned int u_id;
	inline unsigned int get_next_uid() {return u_id++;}

	//скрываем (синглтон же)
	ResourceManager() {};
	~ResourceManager();
	ResourceManager(const ResourceManager&) {};
	ResourceManager& operator=(const ResourceManager&) {};
};

//короткое название
typedef ResourceManager RM;
#endif