#include "GameObjectManager.h"

GameObjectType::GameObjectType(const std::string& _typeName, const luaponte::object& _function) 
: typeName(_typeName), function(_function)
{

}

GameObjectType::GameObjectType(GameObjectType&& got) : goList(std::move(got.goList)), function(got.function)
, go_it(got.go_it), typeName(std::move(got.typeName)) 
{

}

//creates singleton
GameObjectManager& GOM::get_instance()
{
	static GameObjectManager singleton;
	return singleton;
}


//functions to operate with objects and types
void GOM::create_object_type(const std::string& typeName, const luaponte::object& function)
{
	typeMap.insert( std::make_pair(typeName, GameObjectType(typeName, function)) );
}

GameObject& GOM::create_object(const std::string& typeName, const std::string& objectName)
{
	auto& type = typeMap.at(typeName);
	//creating game object
	type.goList.push_back( GameObject(typeName, objectName) );
	//calling Lua function and passing game object to it
	type.function["Initialize"](&type.goList.back());

	return type.goList.back();
}

GameObject& GOM::get_object(const std::string& typeName, const std::string& objectName)
{
	auto& type = typeMap.at(typeName);
	for(auto& go : type.goList){
		if (go.objectName == objectName){
			return go;
		}
	}
}

bool GOM::delete_object(const std::string& typeName, const std::string& objectName)
{
	auto& type = typeMap.at(typeName);
	for(auto it = type.goList.begin(), end = type.goList.end(); it != end; ++it){
		if (it->objectName == objectName){
			//calling Lua function and passing game object to it
			type.function["Release"](&(*it));
			type.goList.erase(it);
			return true;
		}
	}
	return false;
}

bool GOM::delete_object(GameObject& go)
{
	const std::string& typeName = go.typeName;
	const std::string& objectName = go.objectName;
	auto& type = typeMap.at(typeName);
	for(auto it = type.goList.begin(), end = type.goList.end(); it != end; ++it){
		if (it->objectName == objectName){
			//calling Lua function and passing game object to it
			type.function["Release"](&(*it));
			type.goList.erase(it);
			return true;
		}
	}
	return false;	
}

//functions to roam in Lua through the list of all objects (ignoring their type)
GameObject& GOM::global_get_next()
{
	GameObject& returnValue = *go_it;
	go_it++;
	//if the end is reached
	if (go_it == type_it->second.goList.end()){
		while (type_it != typeMap.end() && type_it->second.goList.size() == 0)
			type_it++;
		if (type_it != typeMap.end())
			go_it = type_it->second.goList.begin();
	}
	return returnValue;
}

void GOM::global_reset()
{
	if (global_size == 0){
		return;
	}
	for(auto it = typeMap.begin(), end = typeMap.end(); it != end; ++it){
		if (it->second.goList.size() != 0){
			type_it = it;
			go_it = it->second.goList.begin();
			break;
		}
	}
}

bool GOM::global_end_reached() const
{
	if (global_size == 0){
		return true;
	}
	if (type_it == typeMap.end()){
		return true;
	}
	return false;
}

int GOM::global_get_size() const
{
	return global_size;
}

//functions to roam in Lua through the list of objets of a specific type
GameObject& GOM::get_next(const std::string& typeName)
{
	auto& type = typeMap.at(typeName);
	GameObject& returnValue = *type.go_it;
	type.go_it++;
	return returnValue;
}
void GOM::reset(const std::string& typeName)
{
	auto& type = typeMap.at(typeName);
	type.go_it = type.goList.begin();
}

bool GOM::end_reached(const std::string& typeName) const
{
	auto& type = typeMap.at(typeName);
	return (type.go_it == type.goList.end());
}

int GOM::get_size(const std::string& typeName) const
{
	return typeMap.at(typeName).goList.size();
}