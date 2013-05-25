#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <string>
#include <memory>
#include "../BaseComponent.h"
#include "../../BaseObject.h"
#include "../../ResourceManager/AnimationResource.h"

class Animation : public BaseComponent, public BaseObject{
public:
	//all Animations parameters
	struct Parameters{
		std::shared_ptr<AnimationResource> currentResource;
		std::string currentStateName;

		unsigned int animationSpeed;
		unsigned int renderLay;
		unsigned int currentSprite;
		unsigned int frameToWait;
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
	bool add_state(const std::string stateName, const std::string resName);
	bool add_state(const std::string stateName, const std::shared_ptr<AnimationResource> res);
	//get/set current state
	std::string get_state() const { return params.currentStateName; }
	bool set_state(const std::string stateName);

	//get/set animation speed
	unsigned int get_speed() const { return params.animationSpeed; }
	void set_speed(unsigned int s);

	//get/set render lay
	unsigned int get_lay() const { return params.renderLay; }
	void set_lay(unsigned int l) { params.renderLay = l; }

	//returns copy of current parameters
	Parameters get_params() const { return params; }

	Animation(const std::string name, const unsigned int id);
	~Animation() {};
private:
	std::map<std::string, std::shared_ptr<AnimationResource>> stateMap;
	Parameters params;

	Animation();
	Animation(const Animation&);
	Animation& operator=(const Animation&);
};

#endif