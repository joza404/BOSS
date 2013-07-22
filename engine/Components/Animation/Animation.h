#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <string>
#include <memory>
#include <map>

#include "../BaseComponent.h"
#include "../../BaseObject.h"
#include "../../Resources/AnimationResource.h"
#include "../Position/Position.h"

class Animation : public BaseComponent, public BaseObject{
public:
	//all Animations parameters
	struct Parameters{
		AnimationResource* currentResource = nullptr;
		std::string currentStateName;

		unsigned int animationSpeed;
		unsigned int renderLayer;
		bool regedInRenderer;
		unsigned int currentSprite;
		int frameToWait;
		unsigned int spriteCount;

		int x, y;
		unsigned int w, h;
		unsigned int sprite_x_offset;
		unsigned int sprite_y_offset;

		bool speed_changed;
		bool state_changed;
	};
	//component update function
	void update();

	//the resource also has to be inside res manager 
	void add_state(const std::string& stateName, const std::string& resName);
	void add_state(const std::string& stateName, AnimationResource& res);

	//get/set current state
	std::string get_state() const;
	bool set_state(const std::string&);

	//get/set animation speed
	unsigned int get_speed() const;
	void set_speed(unsigned int);

	//get/set render layer
	unsigned int get_layer() const;
	bool set_layer(unsigned int);

	//returns copy of current parameters
	Parameters get_params() const;

	//set references to other components
	void set_position(Position* pos);
	void set_position(const std::string&);
	void unset_position();

	Animation(const std::string& name);
	~Animation();
	Animation() = delete;
	Animation(const Animation&) = delete;
	Animation& operator=(const Animation&) = delete;

private:
	std::map<std::string, AnimationResource*> stateMap;
	Parameters params;

	//references to other components
	Position* positionComp = nullptr;
};

#endif