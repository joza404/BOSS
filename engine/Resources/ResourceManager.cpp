#include "ResourceManager.h"

//creates singleton
ResourceManager& RM::get_instance()
{
	static ResourceManager singleton;
	return singleton;
}

//loading resources
AnimationResource& RM::load_animation_res(const std::string& name, const std::string& path)
{
	animationMap.insert( std::make_pair(name, AnimationResource(name, path)) );
	return animationMap.at(name);
}

ImageResource& RM::load_image_res(const std::string& name, const std::string& path)
{
	imageMap.insert( std::make_pair(name, ImageResource(name, path)) );
	return imageMap.at(name);
}

FontResource& RM::load_font_res(const std::string& name, const std::string& path)
{
	fontMap.insert( std::make_pair(name, FontResource(name, path)) );
	return fontMap.at(name);
}

RigidBodyResource& RM::load_rigidbody_res(const std::string& name, const std::string& path)
{
	rigidBodyMap.insert( std::make_pair(name, RigidBodyResource(name, path)) );
	return rigidBodyMap.at(name);
}

//getting resources
AnimationResource& RM::get_animation_res(const std::string& name)
{
	return animationMap.at(name);
}

ImageResource& RM::get_image_res(const std::string& name)
{
	return imageMap.at(name);
}

FontResource& RM::get_font_res(const std::string& name)
{
	return fontMap.at(name);
}

RigidBodyResource& RM::get_rigidbody_res(const std::string& name)
{
	return rigidBodyMap.at(name);
}