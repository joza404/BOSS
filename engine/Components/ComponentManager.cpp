#include "ComponentManager.h"

ComponentManager& CM::get_instance()
{
	static ComponentManager singleton;
	return singleton;
}

void CM::update_components()
{
	for(auto& it : animationMap) it.second->update();
	for(auto& it : imageMap) it.second->update();
	for(auto& it : textMap) it.second->update();
	for(auto& it : positionMap) it.second->update();
	for(auto& it : movementMap) it.second->update();
}

//creating components
Animation* CM::create_animation_comp(const std::string& name)
{
	animationMap.insert( std::make_pair(name, std::unique_ptr<Animation>(new Animation(name))) );
	return animationMap.at(name).get();
}

Image* CM::create_image_comp(const std::string& name)
{
	imageMap.insert( std::make_pair(name, std::unique_ptr<Image>(new Image(name))) );
	return imageMap.at(name).get();
}

Text* CM::create_text_comp(const std::string& name)
{
	textMap.insert( std::make_pair(name, std::unique_ptr<Text>(new Text(name))) );
	return textMap.at(name).get();
}

Position* CM::create_position_comp(const std::string& name)
{
	positionMap.insert( std::make_pair(name, std::unique_ptr<Position>(new Position(name))) );
	return positionMap.at(name).get();
}

Movement* CM::create_movement_comp(const std::string& name)
{
	movementMap.insert( std::make_pair(name, std::unique_ptr<Movement>(new Movement(name))) );
	return movementMap.at(name).get();
}

//getting components
Animation* CM::get_animation_comp(const std::string& name)
{
	return animationMap.at(name).get();
}

Image* CM::get_image_comp(const std::string& name)
{
	return imageMap.at(name).get();
}

Text* CM::get_text_comp(const std::string& name)
{
	return textMap.at(name).get();
}

Position* CM::get_position_comp(const std::string& name)
{
	return positionMap.at(name).get();
}

Movement* CM::get_movement_comp(const std::string& name)
{
	return movementMap.at(name).get();
}

//deleting components
void CM::delete_animation_comp(const std::string& name)
{
	animationMap.erase(name);
}

void CM::delete_image_comp(const std::string& name)
{
	imageMap.erase(name);
}

void CM::delete_text_comp(const std::string& name)
{
	textMap.erase(name);
}

void CM::delete_position_comp(const std::string& name)
{
	positionMap.erase(name);
}

void CM::delete_movement_comp(const std::string& name)
{
	movementMap.erase(name);
}

void CM::delete_animation_comp(Animation* animation)
{
	animationMap.erase(animation->name);
}

void CM::delete_image_comp(Image* image)
{
	imageMap.erase(image->name);
}

void CM::delete_text_comp(Text* text)
{
	textMap.erase(text->name);
}

void CM::delete_position_comp(Position* position)
{
	positionMap.erase(position->name);
}

void CM::delete_movement_comp(Movement* movement)
{
	movementMap.erase(movement->name);
}
