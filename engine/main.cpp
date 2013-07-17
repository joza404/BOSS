#include <locale>
#include <iostream>
#include <memory>
#include <type_traits>

#include <SDL_ttf.h>
#include <SDL.h>
#include <Lua.hpp>
#include <luaponte\luaponte.hpp>
#include <luaponte\object.hpp>

#include "globals.h"

#include "Input\Input.h"

#include "ResourceManager\ResourceManager.h"
#include "ResourceManager\AnimationResource.h"
#include "ResourceManager\FontResource.h"
#include "ResourceManager\ImageResource.h"

#include "Components\ComponentManager.h"
#include "Components\Animation\Animation.h"
#include "Components\Position\Position.h"
#include "Components\Image\Image.h"
#include "Components\Text\Text.h"

#include "Renderer\Renderer.h"

#include "Lua\Lua.h"

class Testing{
public:
	void print() {std::cout << "BUR!\n\r";}
	Testing() {std::cout << "Testing default constructor.\n\r";}
	Testing(const Testing& test) {std::cout << "Testing copy constructor.\n\r";}
	Testing& operator=(const Testing& test) {std::cout << "Testing operator=\n\r";}
};

class Bur{
public:
	Bur() {test2 = new Testing(); test3 = std::shared_ptr<Testing>(new Testing);}
	Testing test1;
	Testing* test2;
	std::shared_ptr<Testing> test3;
	Testing& get(){ return test1; }
};

int main(int argc,char* argv[])
{
	setlocale(LC_ALL, "russian_russia.1251");
	TTF_Init();

	//renderer MUST be placed before component manager
	Renderer* r = Renderer::get_instance();
	ResourceManager* rm = ResourceManager::get_instance();
	ComponentManager* cm = ComponentManager::get_instance();
	Lua* lua = Lua::get_instance();
	Input* input = Input::get_instance();

	r->create_window(WINDOW_CAPTION, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_BIT_FORMAT, WINDOW_FPS);
	lua->bind_all();

	using namespace luaponte;
	module(lua->get_state())
	[
		class_<Bur>("Bur")
		.def(constructor<>())
		.def_readwrite("test1", &Bur::test1)
		.def_readwrite("test2", &Bur::test2)
		.def_readwrite("test3", &Bur::test3)
		.def("get",&Bur::get),

		class_<Testing, std::shared_ptr<Testing> >("Testing")
		.def("print", &Testing::print)
	];

	lua->do_file(LUA_INIT_SCRIPT);	
	
	auto boy2 = cm->create_component<Animation>("boy2");
	boy2->add_state("boy_stay", "boy_stay");
	boy2->add_state("boy_reversed_stay", "boy_reversed_stay");
	boy2->set_state("boy_stay");

	//cm->create_component<Position>("boy_position");
	auto random_pos = cm->create_component<Position>("random_position");

	//cm->get_component<Animation>("boy")->set_position("boy_position");

	//image TESTS
	//auto spaceRes = rm->load_resource<ImageResource>("..//game//images//bg.info", "space");
	auto x = cm->create_component<Image>("background"); 
	if (rm->get_resource<ImageResource>("space") != false) x->set_resource(rm->get_resource<ImageResource>("space"));
	//auto y = cm->create_component<Image>("background2"); y->set_resource("space");
	//auto z = cm->create_component<Image>("background3"); z->set_resource("space");

	//text TESTS
	auto text1 = cm->create_component<Text>("text1"); 
	text1->set_resource(rm->get_resource<FontResource>("font1"));
	text1->set_text("hello world!");

	luaponte::object    m_CurrentState;
	cm->update_components();
	r->render();

	SDL_Event event;

	//game loop
	while (true){
		r->fps_start();
		/*
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
		}*/
		input->handle();

		cm->update_components();
		r->render();

		r->fps_end();
	}
	
	return 0;
}