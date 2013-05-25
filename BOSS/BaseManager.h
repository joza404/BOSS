#ifndef _BASE_MANAGER_H_
#define _BASE_MANAGER_H_

#include <string>
#include <map>

template <typename T>
class BaseMapManager{
public:
	//adds element T to maps
	T add(T element, std::string name){
		nameMap[name] = element;
		idMap[id] = element;
		id++;
		return element;
	}
	//removes element T from maps
	T remove(T element){
		nameMap.erase(element->name);
		idMap.erase(element->id);
		return element;
	}
	T remove(std::string name){
		try{
			T element = nameMap.at(name); 
			remove(element);
			return element;
		}
		catch (...){
			throw;
		}
	}
	T remove(unsigned int id){
		try{
			T element = idMap.at(id); 
			remove(element);
			return element;
		}
		catch (...){
			throw;
		}
	}
	//returns element T from maps (but doesn't remove it)
	T get(std::string name){
		try{
			T element = nameMap.at(name); 
			return element;
		}
		catch (...){
			throw;
		}
	}
	T get(unsigned int id){
		try{
			T element = idMap.at(id); 
			return element;
		}
		catch (...){
			throw;
		}
	}

	unsigned int get_id() { return id; }

	BaseMapManager() { id = 0; };
	~BaseMapManager() { nameMap.clear(); idMap.clear(); };

protected:
	std::map<std::string, T> nameMap;
	std::map<unsigned int, T> idMap;

	//each element of type T gets new unique id
	unsigned int id;

	//hide it
	BaseMapManager(const BaseMapManager&) {};
	BaseMapManager& operator=(const BaseMapManager&) {};
};

#endif