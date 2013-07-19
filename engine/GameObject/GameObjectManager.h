#ifndef _GAME_OBJECT_MANAGER_H_
#define _GAME_OBJECT_MANAGER_H_

#include <string>
#include <memory>
#include <list>
#include <map>

#include <Lua.hpp>
#include <luaponte\luaponte.hpp>
#include <luaponte\object.hpp>

#include "GameObject.h"

struct GameObjectType{
	const std::string typeName;
	//the list of the game objects with the same type name
	std::list<GameObject> goList;

	//lua function which will be called to init new object of this type 
	luaponte::object function;

	//iterator for a local roaming through the goList
	std::list<GameObject>::iterator go_it;

	GameObjectType(const std::string& _typeName, const luaponte::object& _function) 
	: typeName(_typeName), function(_function) {};

	GameObjectType(GameObjectType&& got) : goList(std::move(got.goList)), function(got.function)
	, go_it(got.go_it), typeName(std::move(got.typeName)) {}
};

class GameObjectManager{
public:
	//creates singleton
	static GameObjectManager* get_instance(){
		static GameObjectManager singleton;
		return &singleton;
	}

	//functions to operate with objects and types
	void create_object_type(const std::string&, const luaponte::object&);
	GameObject& create_object(const std::string&, const std::string&);
	GameObject& get_object(const std::string&, const std::string&);
	bool delete_object(const std::string&, const std::string&);
	bool delete_object(GameObject&);

	//functions to roam in Lua through the list of all objects (ignoring their type)
	GameObject& global_get_next();
	void global_reset();
	bool global_end_reached() const;
	int global_get_size() const;

	//functions to roam in Lua through the list of objets of a specific type
	GameObject& get_next(const std::string&);
	void reset(const std::string&);
	bool end_reached(const std::string&) const;
	int get_size(const std::string&) const;

	//each map element contain the list of the game objects with the same type name
	std::map<std::string, GameObjectType> typeMap;

private:
	//iterators for a global roaming
	std::map<std::string, GameObjectType>::iterator type_it;
	std::list<GameObject>::iterator go_it;

	//number of the all game objects
	int global_size;

	//hide it (singleton)
	GameObjectManager() = default;
	~GameObjectManager() = default;
	GameObjectManager(const GameObjectManager&) = delete;
	GameObjectManager& operator=(const GameObjectManager&) = delete;
};

typedef GameObjectManager GOM;
typedef GameObjectType GOT;

#endif