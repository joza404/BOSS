#include <locale>
#include <SDL_ttf.h>
#include <SDL.h>
#include <memory>

#include "globals.h"

#include "ResourceManager\ResourceManager.h"
#include "Components\ComponentManager.h"
#include "Renderer\Renderer.h"

#include "ResourceManager\AnimationResource.h"
#include "ResourceManager\FontResource.h"
#include "ResourceManager\ImageResource.h"
#include "Components\Animation\Animation.h"
#include "Components\Position\Position.h"
#include "Components\Image\Image.h"
#include "Components\Text\Text.h"

int main(int argc,char** argv)
{
	setlocale(LC_ALL, "russian_russia.1251");
	TTF_Init();

	//renderer MUST be placed before component manager
	Renderer* r = Renderer::get_instance();
	ResourceManager* rm = ResourceManager::get_instance();
	ComponentManager* cm = ComponentManager::get_instance();
	

	//renderer TESTS
	r->create_window(WINDOW_CAPTION, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_BIT_FORMAT, WINDOW_FPS);

	//animation TESTS
	rm->load_resource<AnimationResource>("..//game//images//standingboy.info", "boy_stay");
	rm->load_resource<AnimationResource>("..//game//images//standingboy2.info", "boy_reversed_stay");

	auto boy = cm->create_component<Animation>("boy");
	boy->add_state("boy_stay", "boy_stay");
	boy->add_state("boy_reversed_stay", "boy_reversed_stay");
	boy->set_state("boy_stay");

	cm->create_component<Position>("boy_position");
	auto& random_pos = cm->create_component<Position>("random_position");

	cm->get_component<Animation>("boy")->set_position("boy_position");

	//image TESTS
	auto spaceRes = rm->load_resource<ImageResource>("..//game//images//bg.info", "space");
	auto x = cm->create_component<Image>("background"); //x->set_resource(rm->get_resource<ImageResource>("space"));
	auto y = cm->create_component<Image>("background2"); y->set_resource(spaceRes);
	auto z = cm->create_component<Image>("background3"); //z->set_resource("space");

	//text TESTS
	auto font1 = rm->load_resource<FontResource>("..//game//fonts//font1.info", "font1");
	auto text1 = cm->create_component<Text>("text1"); 
	text1->set_resource(font1);
	text1->set_text("hello world!");

	
	cm->update_components();
	r->render();

	SDL_Event event;

	//game loop
	while (true){
		r->fps_start();

		SDL_PollEvent(&event);
		if (event.type == SDL_KEYDOWN){
			if (event.key.keysym.sym == SDLK_LEFT){
				break;
			}
			if (event.key.keysym.sym == SDLK_SPACE){
				if (cm->get_component<Animation>("boy")->get_state() == "boy_stay"){
					cm->get_component<Animation>("boy")->set_state("boy_reversed_stay");
				} else
				if (cm->get_component<Animation>("boy")->get_state() == "boy_reversed_stay"){
					cm->get_component<Animation>("boy")->set_state("boy_stay");
				}
				cm->get_component<Text>("text1")->set_position(random_pos);
				cm->get_component<Position>("random_position")->set_x(300);
				cm->get_component<Position>("random_position")->set_y(300);
			}
			if (event.key.keysym.sym == SDLK_DOWN){
				cm->get_component<Animation>("boy")->set_speed(cm->get_component<Animation>("boy")->get_speed()+1);
				cm->get_component<Text>("text1")->set_color(0x00FF00FF);
				cm->get_component<Text>("text1")->set_text("HOLA");
				
			}
			if (event.key.keysym.sym == SDLK_RIGHT){
				cm->get_component<Position>("boy_position")->set_x(cm->get_component<Position>("boy_position")->get_x()+1);
				cm->get_component<Text>("text1")->set_color(0x00FFFFFF);
				cm->get_component<Position>("random_position")->set_x(100);
			}
		}

		cm->update_components();
		r->render();

		r->fps_end();
	}
	
	return 0;
}