#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_

#include <memory>
#include "../BaseManager.h"
#include "AnimationResource.h"
#include "FontResource.h"
#include "ImageResource.h"

class ResourceManager{
public:
	//creates singleton
	static ResourceManager* init(){
		static ResourceManager singleton;
		return &singleton;
	}

	template <typename T>
	bool load_resource(std::string path, std::string name){
		auto& targetMap = get_map<std::shared_ptr<T>>();
		try{
			targetMap.add(std::shared_ptr<T>(new T(path, name, targetMap.get_id())), name);
			return true;
		}
		catch (...){
			//the resource hasn't been loaded properly
			return false;
		}
	}

	template <typename T>
	std::shared_ptr<T> get_resource(std::string name){
		try{
			return get_map<std::shared_ptr<T>>().get(name);
		}
		catch (...){
			//the resource is not in the maps
			return std::shared_ptr<T>();
		}
	}

	template <typename T>
	std::shared_ptr<T> get_resource(unsigned int id){
		try{
			return get_map<std::shared_ptr<T>>().get(id);
		}
		catch (...){
			//the resource is not in the maps
			return std::shared_ptr<T>();
		}
	}

private:
	BaseMapManager<std::shared_ptr<AnimationResource>> animationMap;
	BaseMapManager<std::shared_ptr<ImageResource>> imageMap;
	BaseMapManager<std::shared_ptr<FontResource>> fontMap;

	//gets certain map depends on template argument
	template <typename T> BaseMapManager<T>& get_map();
	template <> BaseMapManager<std::shared_ptr<AnimationResource>>& get_map(){ return animationMap; }
	template <> BaseMapManager<std::shared_ptr<ImageResource>>& get_map(){ return imageMap; }
	template <> BaseMapManager<std::shared_ptr<FontResource>>& get_map(){ return fontMap; }

	//hide it (singleton)
	ResourceManager() {};
	~ResourceManager() {};
	ResourceManager(const ResourceManager&) {};
	ResourceManager& operator=(const ResourceManager&) {};
};

typedef ResourceManager RM;
#endif