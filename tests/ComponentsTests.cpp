#include <cassert>

#include "../engine/Components/ComponentManager.h"
#include "../engine/Components/Animation/Animation.h"
#include "../engine/Components/Image/Image.h"
#include "../engine/Components/Text/Text.h"
#include "../engine/Components/Position/Position.h"
#include "../engine/Resources/ResourceManager.h"
#include "../engine/Resources/AnimationResource.h"

void test_components()
{
	auto& rm = ResourceManager::get_instance();
	auto& cm = ComponentManager::get_instance();
	AnimationResource& boy_res1 = rm.load_animation_res("boy_res1", "..//game//resources//standingboy.info");
	rm.load_animation_res("boy_res2", "..//game//resources//standingboy2.info");

	Animation* boy = cm.create_animation_comp("boy");
	boy->add_state("boy_up", boy_res1);
	boy->add_state("boy_down", "boy_res2");
	
	boy->set_state("boy_up");
	boy->set_position(cm.create_position_comp("boy_pos"));

	rm.load_image_res("space",  "..//game//resources//space.info");
	cm.create_image_comp("background")->set_resource("space");

	rm.load_font_res("font1", "..//game//resources//font1.info");
	cm.create_text_comp("text1")->set_resource("font1");
	cm.get_text_comp("text1")->set_text("Hello wolrd!");
}