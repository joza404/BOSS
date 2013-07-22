#ifndef _COMPONENT_MANAGER_H_
#define _COMPONENT_MANAGER_H_

#include <string>
#include <map>
#include <memory>

#include "Animation\Animation.h"
#include "Image\Image.h"
#include "Text\Text.h"
#include "Position\Position.h"
#include "Movement\Movement.h"

class ComponentManager{
public:
	//creates sigleton
	static ComponentManager& get_instance();

	void update_components();

	Animation* create_animation_comp(const std::string& name);
	Image* create_image_comp(const std::string& name);
	Text* create_text_comp(const std::string& name);
	Position* create_position_comp(const std::string& name);
	Movement* create_movement_comp(const std::string& name);

	Animation* get_animation_comp(const std::string& name);
	Image* get_image_comp(const std::string& name);
	Text* get_text_comp(const std::string& name);
	Position* get_position_comp(const std::string& name);
	Movement* get_movement_comp(const std::string& name);

	void delete_animation_comp(const std::string& name);
	void delete_image_comp(const std::string& name);
	void delete_text_comp(const std::string& name);
	void delete_position_comp(const std::string& name);
	void delete_movement_comp(const std::string& name);

	void delete_animation_comp(Animation*);
	void delete_image_comp(Image*);
	void delete_text_comp(Text*);
	void delete_position_comp(Position*);
	void delete_movement_comp(Movement*);

private:
	std::map<std::string, std::unique_ptr<Animation> > animationMap;
	std::map<std::string, std::unique_ptr<Image> > imageMap;
	std::map<std::string, std::unique_ptr<Text> > textMap;
	std::map<std::string, std::unique_ptr<Position> > positionMap;
	std::map<std::string, std::unique_ptr<Movement> > movementMap;

	//hide it (singleton)
	ComponentManager() = default;
	~ComponentManager() = default;
	ComponentManager(const ComponentManager&) = delete;
	ComponentManager& operator=(const ComponentManager&) = delete;
};

typedef ComponentManager CM;

#endif