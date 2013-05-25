#include <string>
#include "Animation.h"
#include "../../ResourceManager/ResourceManager.h"

void Animation::update()
{
	params.frameToWait--;
	if (params.frameToWait <= 0){
		params.frameToWait = params.animationSpeed - 1;
	}

	if (params.speed_changed){
		params.frameToWait = params.animationSpeed - 1;
	}

	if (params.animationSpeed == 0){
		params.frameToWait = 1;
	}

	if (params.state_changed){
		params.frameToWait = 0;
	}

	//change sprite
	if (params.frameToWait == 0){
		params.sprite_x_offset += params.w;
		params.currentSprite++;
	}
	//set current sprite to first
	if (params.currentSprite == params.spriteCount){
		params.sprite_x_offset = 0;
		params.currentSprite = 0;
	}
}

bool Animation::add_state(const std::string stateName, const std::string resName)
{
	auto res = ResourceManager::init()->get_resource<AnimationResource>(resName);
	if (!res) return false;
	stateMap[stateName] = res;
	return true;
}

bool Animation::add_state(const std::string stateName, const std::shared_ptr<AnimationResource> res)
{
	if (!res) return false;
	stateMap[stateName] = res;
	return true;
}

bool Animation::set_state(const std::string stateName)
{
	
	auto it = stateMap.find(stateName);
	if (it == stateMap.end()) //element with that name is not found
		return false;

	params.currentStateName = stateName;
	params.currentResource = it->second;
	params.spriteCount = it->second->spriteCount;
	params.currentSprite = 0;
	params.sprite_x_offset = 0;
	params.sprite_y_offset = 0;
	params.w = it->second->image->w;
	params.h = it->second->image->h;
	params.frameToWait = 0; //render it immediately
	params.state_changed = true;
	return true;
}

void Animation::set_speed(unsigned int s) { 
	params.animationSpeed = s;
	params.speed_changed = true;
}

Animation::Animation(const std::string _name, const unsigned int _id) :  BaseObject(_name, _id){
	params.animationSpeed = 1;
	params.currentSprite = 0;
	params.frameToWait = 0;
	params.h = params.w = params.x = params.y = 0;
	params.renderLay = 1;
	params.speed_changed = false;
	params.spriteCount = 0;
	params.sprite_x_offset = 0;
	params.sprite_y_offset = 0;
	params.state_changed = false;
}