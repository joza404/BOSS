#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_

#include <string>
#include <map>

#include "AnimationResource.h"
#include "FontResource.h"
#include "ImageResource.h"
#include "RigidBodyResource.h"

class ResourceManager{
public:
	//creates singleton
	static ResourceManager& get_instance();

	AnimationResource& load_animation_res(const std::string& name, const std::string& path);
	ImageResource& load_image_res(const std::string& name, const std::string& path);
	FontResource& load_font_res(const std::string& name, const std::string& path);
	RigidBodyResource& load_rigidbody_res(const std::string& name, const std::string& path);

	AnimationResource& get_animation_res(const std::string& name);
	ImageResource& get_image_res(const std::string& name);
	FontResource& get_font_res(const std::string& name);
	RigidBodyResource& get_rigidbody_res(const std::string& name);

private:
	std::map<std::string, AnimationResource> animationMap;
	std::map<std::string, ImageResource> imageMap;
	std::map<std::string, FontResource> fontMap;
	std::map<std::string, RigidBodyResource> rigidBodyMap;

	//hide it (singleton)
	ResourceManager() = default;
	~ResourceManager() = default;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
};

typedef ResourceManager RM;

#endif