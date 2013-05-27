#include <string>
#include "Animation.h"
#include "../../ResourceManager/ResourceManager.h"
#include "../ComponentManager.h"
#include "../../Renderer/Renderer.h"

//local macroses (in .cpp)
#define DEFAULT_ANIMATION_SPEED 1
#define DEFAULT_RENDER_LAYER 1
#define DEFAULT_X 0
#define DEFAULT_Y 0

void Animation::update()
{
	params.frameToWait--;
	if (params.frameToWait < 0){
		params.frameToWait = params.animationSpeed - 1;
	}

	if (params.speed_changed){
		params.frameToWait = params.animationSpeed - 1;
		params.speed_changed = false;
	}

	if (params.animationSpeed == 0){
		params.frameToWait = 1;
	}

	if (params.state_changed){
		params.frameToWait = 0;
		params.state_changed = false;
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

	//if position component exists
	if (positionComp.expired() == false){
		auto shared = positionComp.lock();
		params.x = shared->get_x();
		params.y = shared->get_y();
	}
}

bool Animation::add_state(const std::string& stateName, const std::string& resName)
{
	auto res = ResourceManager::get_instance()->get_resource<AnimationResource>(resName);
	if (!res) return false;
	stateMap[stateName] = res;
	return true;
}

bool Animation::add_state(const std::string& stateName, const std::shared_ptr<AnimationResource>& res)
{
	if (!res) return false;
	stateMap[stateName] = res;
	return true;
}

bool Animation::set_state(const std::string& stateName)
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
	params.w = it->second->image->w / params.spriteCount;
	params.h = it->second->image->h;
	params.frameToWait = 0; //render it immediately
	params.state_changed = true;
	return true;
}

bool Animation::set_layer(unsigned int layer)
{
	Renderer* renderer = Renderer::get_instance();
	if (renderer->last_layer() > layer)
		return false;

	renderer->unregister_component(this, params.renderLayer);
	params.renderLayer = layer;
	renderer->register_component(this, layer);
	return true;
}

void Animation::set_speed(unsigned int s)
{
	params.animationSpeed = s;
	params.speed_changed = true;
}

void Animation::set_position(const std::string& pos)
{
	positionComp = ComponentManager::get_instance()->get_component<Position>(pos);
}

Animation::Animation(const std::string& _name, const unsigned int _id) :  BaseObject(_name, _id)
{
	params.animationSpeed = DEFAULT_ANIMATION_SPEED;
	params.currentSprite = 0;
	params.frameToWait = 0;
	params.h = params.w = 0;
	params.x = DEFAULT_X;
	params.y = DEFAULT_Y;
	params.renderLayer = DEFAULT_RENDER_LAYER;
	params.speed_changed = false;
	params.spriteCount = 0;
	params.sprite_x_offset = 0;
	params.sprite_y_offset = 0;
	params.state_changed = false;

	Renderer::get_instance()->register_component(this, params.renderLayer);
}

Animation::~Animation()
{
	Renderer::get_instance()->unregister_component(this, params.renderLayer);
}