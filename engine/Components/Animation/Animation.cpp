#include <string>

#include "Animation.h"
#include "../../Resources/ResourceManager.h"
#include "../ComponentManager.h"
#include "../../Renderer/Renderer.h"

//local macroses (in .cpp)
#define DEFAULT_ANIMATION_SPEED 1
#define DEFAULT_RENDER_LAYER 2
#define DEFAULT_X 0
#define DEFAULT_Y 0

//component update function
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
	if (positionComp != nullptr){
		params.x = positionComp->get_x();
		params.y = positionComp->get_y();
	}
}

//the resource also has to be inside res manager 
void Animation::add_state(const std::string& stateName, const std::string& resName)
{
	AnimationResource& res = ResourceManager::get_instance().get_animation_res(resName);
	stateMap.insert( std::make_pair(stateName, &res) );
}

void Animation::add_state(const std::string& stateName, AnimationResource& res)
{
	stateMap.insert( std::make_pair(stateName, &res) );
}

//get/set current state
std::string Animation::get_state() const 
{ 
	return params.currentStateName; 
}

bool Animation::set_state(const std::string& stateName)
{
	
	auto it = stateMap.find(stateName);
	if (it == stateMap.end()) //element with that name is not found
		return false;

	params.currentStateName = stateName;
	params.currentResource = it->second;
	params.spriteCount = it->second->spriteNumber;
	params.currentSprite = 0;
	params.sprite_x_offset = 0;
	params.sprite_y_offset = 0;
	params.w = it->second->image->w / params.spriteCount;
	params.h = it->second->image->h;
	params.frameToWait = 0; //render it immediately
	params.state_changed = true;

	//first time here
	if (params.regedInRenderer == false){
		Renderer::get_instance().register_component(this, params.renderLayer);
		params.regedInRenderer = true;
	}
	return true;
}

//get/set animation speed
unsigned int Animation::get_speed() const 
{ 
	return params.animationSpeed; 
}

void Animation::set_speed(unsigned int s)
{
	params.animationSpeed = s;
	params.speed_changed = true;
}

//get/set render layer
bool Animation::set_layer(unsigned int layer)
{
	Renderer& renderer = Renderer::get_instance();
	if (renderer.last_layer() > layer)
		return false;

	params.renderLayer = layer;
	if (params.regedInRenderer == true){
		renderer.unregister_component(this, params.renderLayer);	
		renderer.register_component(this, layer);
	}
	return true;
}

unsigned int Animation::get_layer() const 
{ 
	return params.renderLayer; 
}

//returns copy of current parameters
Animation::Parameters Animation::get_params() const 
{ 
	return params; 
}

//set references to other components
void Animation::set_position(const std::string& name)
{
	positionComp = ComponentManager::get_instance().get_position_comp(name);
}

void Animation::set_position(Position* pos)
{ 
	positionComp = pos; 
}

void Animation::unset_position() 
{ 
	positionComp = nullptr;
}

Animation::Animation(const std::string& _name) :  BaseObject(_name)
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
	params.regedInRenderer = false;
	positionComp = nullptr;
}

Animation::~Animation()
{
	if (params.regedInRenderer == true)
		Renderer::get_instance().unregister_component(this, params.renderLayer);
}