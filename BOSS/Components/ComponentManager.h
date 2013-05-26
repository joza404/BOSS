#ifndef _COMPONENT_MANAGER_H_
#define _COMPONENT_MANAGER_H_

#include <memory>
#include "..\BaseManager.h"
#include "Position\Position.h"
#include "Animation\Animation.h"
#include "Image\Image.h"

template <typename T>
class UpdateManager : public BaseMapManager<T>{
public:
	//calls update function for an entire map
	void update(){
		for (auto& it : idMap) 
			it.second->update();
	}
};

class ComponentManager{
public:
	//creates singleton
	static ComponentManager* get_instance(){
		static ComponentManager singleton;
		return &singleton;
	}

	template <typename T>
	std::shared_ptr<T> create_component(std::string name){
		auto& targetMap = get_map<std::shared_ptr<T>>();
		try{
			return targetMap.add(std::make_shared<T>(name, targetMap.get_id()), name);	 
		}
		catch (...){
			//the component hasn't been loaded properly
			return std::shared_ptr<T>();
		}
	}

	template <typename T>
	bool delete_component(std::shared_ptr<T> element){
		auto& targetMap = get_map<std::shared_ptr<T>>();
		try{
			targetMap.remove(element);
			return true;
		}
		catch (...){
			//the component hasn't been deleted
			return false;
		}
	}

	template <typename T>
	bool delete_component(std::string name){
		auto& targetMap = get_map<std::shared_ptr<T>>();
		try{
			targetMap.remove(name);
			return true;
		}
		catch (...){
			//the component hasn't been deleted
			return false;
		}
	}

	template <typename T>
	bool delete_component(unsigned int id){
		auto& targetMap = get_map<std::shared_ptr<T>>();
		try{
			targetMap.remove(id);
			return true;
		}
		catch (...){
			//the component hasn't been deleted
			return false;
		}
	}

	template <typename T>
	std::shared_ptr<T> get_component(std::string name){
		try{
			return get_map<std::shared_ptr<T>>().get(name);
		}
		catch (...){
			//the component is not in the maps
			return std::shared_ptr<T>();
		}
	}

	template <typename T>
	std::shared_ptr<T> get_component(unsigned int id){
		try{
			return get_map<std::shared_ptr<T>>().get(id);
		}
		catch (...){
			//the resource is not in the maps
			return std::shared_ptr<T>();
		}
	}

	template <typename T>
	void update(){ get_map<std::shared_ptr<T>>().update(); }

	void update_components(){
		update<Position>();
		update<Animation>();
		update<Image>();
	}

private:
	UpdateManager<std::shared_ptr<Position>> positionMap;
	UpdateManager<std::shared_ptr<Animation>> animationMap;
	UpdateManager<std::shared_ptr<Image>> imageMap;

	//gets certain map depends on template argument
	template <typename T> UpdateManager<T>& get_map();
	template <> UpdateManager<std::shared_ptr<Position>>& get_map(){ return positionMap; }
	template <> UpdateManager<std::shared_ptr<Animation>>& get_map(){ return animationMap; }
	template <> UpdateManager<std::shared_ptr<Image>>& get_map(){ return imageMap; }

	//hide it (singleton)
	ComponentManager() {};
	~ComponentManager() {};
	ComponentManager(const ComponentManager&) {};
	ComponentManager& operator=(const ComponentManager&) {};
};

typedef ComponentManager CM;
#endif