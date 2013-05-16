#ifndef _OBJECT_MANAGER_H_
#define _OBJECT_MANAGER_H_

#include <map>

#include "Objects\Object.h"

class Object;

class ObjectManager{
public:
	//создает единственный экземпляр класса
	static ObjectManager* create_manager();
	//создает и дает ему уникальное имя u_name
	Object* create_object(Resource* res, std::string u_name = "_set_my_name_to_default_lol_");
	//выгружает объект с именем u_name из памяти
	bool destroy_object(std::string u_name);
	//выгружает объект с id == u_id из памяти
	bool destroy_object(unsigned int u_id);
	//выгружает объект obj из памяти
	bool destroy_object(Object* obj);
	
	//Возвращает указатель на объект с именем u_name
	Object* get_object(std::string u_name);
	//Возвращает указатель на объект с id == u_id
	Object* get_object(unsigned int u_id);

private:
	//map для быстрого поиска по ключу, также хранит указатель на объект
	std::map<std::string, Object*> nameMap;
	std::map<unsigned int, Object*> idMap;

	//каждому новому объекту присваивается новый u_id
	static unsigned int u_id;
	inline unsigned int get_next_uid() {return u_id++;}

	//скрываем (синглтон же)
	ObjectManager() {};
	~ObjectManager();
	ObjectManager(const ObjectManager&) {};
	ObjectManager& operator=(const ObjectManager&) {};
};

//короткое название
typedef ObjectManager OM;
#endif