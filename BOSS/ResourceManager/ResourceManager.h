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
	static ResourceManager* get_instance(){
		static ResourceManager singleton;
		return &singleton;
	}

	template <typename T>
	std::shared_ptr<T> load_resource(const std::string& path, const std::string& name){
		auto& targetMap = get_map<std::shared_ptr<T>>();
		try{
			return targetMap.add(std::make_shared<T>(path, name, targetMap.get_id()), name);	 
		}
		catch (...){
			//the resource hasn't been loaded properly
			return std::shared_ptr<T>();
		}
	}

	template <typename T>
	std::shared_ptr<T> get_resource(const std::string& name) const{
		try{
			return get_map<std::shared_ptr<T>>().get(name);
		}
		catch (...){
			//the resource is not in the maps
			return std::shared_ptr<T>();
		}
	}

	template <typename T>
	std::shared_ptr<T> get_resource(unsigned int id) const{
		try{
			return get_map<std::shared_ptr<T>>().get(id);
		}
		catch (...){
			//the resource is not in the maps
			return std::shared_ptr<T>();
		}
	}

private:
	//using mutable to make "get_map" a const function (because it is called by const "get_resource")
	mutable BaseMapManager<std::shared_ptr<AnimationResource>> animationMap;
	mutable BaseMapManager<std::shared_ptr<ImageResource>> imageMap;
	mutable BaseMapManager<std::shared_ptr<FontResource>> fontMap;

	//gets certain map depends on template argument
	template <typename T> BaseMapManager<T>& get_map() const;
	template <> BaseMapManager<std::shared_ptr<AnimationResource>>& get_map() const{ return animationMap; }
	template <> BaseMapManager<std::shared_ptr<ImageResource>>& get_map() const{ return imageMap; }
	template <> BaseMapManager<std::shared_ptr<FontResource>>& get_map() const{ return fontMap; }

	//hide it (singleton)
	ResourceManager() {};
	~ResourceManager() {};
	ResourceManager(const ResourceManager&) {};
	ResourceManager& operator=(const ResourceManager&) {};
};

typedef ResourceManager RM;
#endif