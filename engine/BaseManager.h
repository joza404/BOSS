#ifndef _BASE_MANAGER_H_
#define _BASE_MANAGER_H_

#include <string>
#include <map>

/*
This manager has to store only the pointers (raw or smart),
because it contains two maps (id and name) and each of them has to store
pointers that point to the SAME memory location
*/

template <typename T>
class BaseMapManager{
public:
	//adds element T to maps
	T add(const T& element, const std::string& name){
		nameMap[name] = element;
		idMap[id] = element;
		id++;
		return element; //it copies the pointer
	}
	//removes element T from maps
	bool remove(const T& element){
		nameMap.erase(element->name);
		idMap.erase(element->id);
		return true;
	}
	bool remove(const std::string& name){
		try{
			T element = nameMap.at(name); 
			return remove(element);
		}
		catch (...){
			return false;
		}
	}
	bool remove(unsigned int id){
		try{
			T element = idMap.at(id); 
			return remove(element);;
		}
		catch (...){
			return false;
		}
	}
	//returns element T from maps (but doesn't remove it)
	T& get(const std::string& name) const{
		try{
			return nameMap.at(name);
		}
		catch (...){
			throw;
		}
	}
	T& get(unsigned int id) const{
		try{ 
			return idMap.at(id);
		}
		catch (...){
			throw;
		}
	}

	unsigned int get_id() const{ return id; }

	BaseMapManager() { id = 0; };
	~BaseMapManager() { nameMap.clear(); idMap.clear(); };
	BaseMapManager(const BaseMapManager&) = delete;
	BaseMapManager& operator=(const BaseMapManager&) = delete;

protected:
	//using mutable to make "at" a const function (because it is called by const "get")
	mutable std::map<std::string, T> nameMap;
	mutable std::map<unsigned int, T> idMap;

	//each element of type T gets new unique id
	unsigned int id;
};

#endif