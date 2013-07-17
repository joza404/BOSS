#include "GameObjectManager.h"

//functions to operate with objects and types
void GOM::create_object_type(const std::string& typeName, const luaponte::object& function)
{
	typeMap[typeName] = std::unique_ptr<GameObjectType>(new GameObjectType(typeName, function));
}

GameObject& GOM::create_object(const std::string& typeName, const std::string& objectName)
{
	auto& type = *(typeMap[typeName]);
	//creating game object
	type.goList.push_back( std::unique_ptr<GameObject>(new GameObject(typeName, objectName)) );
	//calling Lua function and passing game object to it
	type.function["Execute"](type.goList.back().get());

	return *type.goList.back();
}

GameObject& GOM::get_object(const std::string& typeName, const std::string& objectName) const
{
	auto& type = *(typeMap.at(typeName));
	//pgo - pointer to the game object
	for(auto& pgo : type.goList){
		if (pgo->objectName == objectName){
			return *pgo;
		}
	}
}

bool GOM::delete_object(const std::string& typeName, const std::string& objectName)
{
	auto& type = *(typeMap[typeName]);
	for(auto it = type.goList.begin(), end = type.goList.end(); it != end; ++it){
		if ((*it)->objectName == objectName){
			type.goList.erase(it);
			return true;
		}
	}
	return false;
}

bool GOM::delete_object(GameObject& go)
{
	std::string typeName = go.typeName;
	std::string objectName = go.objectName;
	auto& type = *(typeMap[typeName]);
	for(auto it = type.goList.begin(), end = type.goList.end(); it != end; ++it){
		if ((*it)->objectName == objectName){
			type.goList.erase(it);
			return true;
		}
	}
	return false;	
}

//functions to roam in Lua through the list of all objects (ignoring their type)
GameObject& GOM::global_get_next()
{
	//dereference the iterator, then dereference the unique ptr
	GameObject& returnValue = **pgo_it;
	pgo_it++;
	//if the end is reached
	if (pgo_it == (*ptype_it->second).goList.end()){
		while (ptype_it != typeMap.end() && (*ptype_it->second).goList.size() == 0)
			ptype_it++;
		if (ptype_it != typeMap.end())
			pgo_it = (*ptype_it->second).goList.begin();
	}
	return returnValue;
}

void GOM::global_reset()
{
	if (global_size == 0){
		return;
	}
	for(auto it = typeMap.begin(), end = typeMap.end(); it != end; ++it){
		if ((*it->second).goList.size() != 0){
			ptype_it = it;
			pgo_it = (*it->second).goList.begin();
			break;
		}
	}
}

bool GOM::global_end_reached() const
{
	if (global_size == 0){
		return true;
	}
	if (ptype_it == typeMap.end()){
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
	auto& type = *(typeMap[typeName]);
	//dereference the iterator, then dereference the unique ptr
	GameObject& returnValue = **type.pgo_it;
	type.pgo_it++;
	return returnValue;
}
void GOM::reset(const std::string& typeName)
{
	auto& type = *(typeMap[typeName]);
	type.pgo_it = type.goList.begin();
}

bool GOM::end_reached(const std::string& typeName) const
{
	auto& type = *(typeMap.at(typeName));
	return (type.pgo_it == type.goList.end());
}

int GOM::get_size(const std::string& typeName) const
{
	return typeMap.at(typeName)->goList.size();
}