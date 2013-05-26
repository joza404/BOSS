#include <locale>
#include <SDL_ttf.h>
#include <memory>

#include "ResourceManager\ResourceManager.h"
#include "Components\ComponentManager.h"

#include "ResourceManager\AnimationResource.h"
#include "ResourceManager\FontResource.h"
#include "ResourceManager\ImageResource.h"
#include "Components\Animation\Animation.h"
#include "Components\Position\Position.h"
#include "Components\Image\Image.h"



int main(int argc,char** argv)
{
	setlocale(LC_ALL, "russian_russia.1251");
	TTF_Init();

	ResourceManager* rm = ResourceManager::get_instance();
	ComponentManager* cm = ComponentManager::get_instance();

	//animation TESTS
	rm->load_resource<AnimationResource>("..//game//images//standingboy.info", "boy_stay");
	rm->load_resource<AnimationResource>("..//game//images//standingboy2.info", "boy_reversed_stay");

	auto boy = cm->create_component<Animation>("boy");
	boy->add_state("boy_stay", "boy_stay");
	boy->add_state("boy_reversed_stay", "boy_reversed_stay");
	boy->set_state("boy_stay");

	cm->create_component<Position>("boy_position");
	cm->create_component<Position>("random_position");

	cm->get_component<Animation>("boy")->set_position("boy_position");

	//image TESTS
	auto spaceRes = rm->load_resource<ImageResource>("..//game//images//bg.info", "space");
	auto x = cm->create_component<Image>("background"); x->set_resource(rm->get_resource<ImageResource>("space"));
	auto y = cm->create_component<Image>("background2"); y->set_resource(spaceRes);
	auto z = cm->create_component<Image>("background3"); z->set_resource("space");

	
	cm->update_components();
	return 0;
}