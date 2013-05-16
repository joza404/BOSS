#include <iostream>
#include <string>

#include <lua.hpp>

#include "globals.h"

#include "ResourceManager\ResourceManager.h"
#include "ObjectManager\ObjectManager.h"
#include "ObjectManager\ObjectList.h"
#include "Renderer\Renderer.h"
#include "Lua\Lua.h"
#include "Input\Input.h"


int main(int argc,char** argv)
{
	setlocale(LC_ALL, "russian_russia.1251");


	ResourceManager* rm = ResourceManager::create_manager();
	ObjectManager* om = ObjectManager::create_manager();
	Renderer* r = Renderer::create_renderer(WINDOW_CAPTION, SCREEN_WIDTH, SCREEN_HEIGHT, 
											SCREEN_BIT_FORMAT, SCREEN_FPS);
	Lua* l = Lua::init();
	Input* input = Input::init(l);

	l->do_file(LUA_INIT_SCRIPT);

	rm->load_resource("resources\\bg.info", "background");
	r->convert_format(rm->get_resource(0));

	rm->load_resource("resources\\standingboy.info", "boyup");
	r->convert_format(rm->get_resource(1));
	r->set_key_color(rm->get_resource(1));
	
	rm->load_resource("resources\\standingboy2.info", "boydown");
	r->convert_format(rm->get_resource(2));
	r->set_key_color(rm->get_resource(2));

	rm->load_resource("resources\\font1.info", "font1");
	rm->load_resource("resources\\font2.info", "font2");

	TextObject* text = (TextObject*)om->create_object(rm->get_resource("font1"), "text1");
	text->x = 100;
	text->y = 100;
	r->register_object(text, 1);
	

	TextObject* text2 = (TextObject*)om->create_object(rm->get_resource("font1"), "text2");
	text2->x = 400;
	text2->y = 400;
	r->register_object(text2, 1);

	om->create_object(rm->get_resource("background"), "bg");
	r->register_object(om->get_object("bg"));

	om->create_object(rm->get_resource("boydown"), "boydown");
	((AO*)om->get_object("boydown"))->create_state(rm->get_resource("boyup"), "boyup");
	r->register_object(om->get_object("boydown"), 1);


	r->render();
	SDL_Event event;

	int i = 0;
	while (true){
		r->fps_start();
		input->handle();
		/*
		SDL_PollEvent(&event);
		if (event.type == SDL_KEYDOWN){
			if (event.key.keysym.sym == SDLK_LEFT){
				((AO*)om->get_object("boydown"))->x--;
			} else
			if (event.key.keysym.sym == SDLK_RIGHT){
				((AO*)om->get_object("boydown"))->x++;
			} else
			if (event.key.keysym.sym == SDLK_DOWN){
				((AO*)om->get_object("boydown"))->y++;
			} else
			if (event.key.keysym.sym == SDLK_UP){
				((AO*)om->get_object("boydown"))->y--;
			} else
			if (event.key.keysym.sym == SDLK_ESCAPE){
				break;
			} 
		}
		*/


		i++;
		if (i == 100){
			((AO*)om->get_object("boydown"))->set_new_state("boyup");
			((TextObject*)om->get_object("text1"))->set_size(40);
		}

		if (i == 1300){
			((AO*)om->get_object("boydown"))->set_new_state("main");
			((TextObject*)om->get_object("text2"))->set_color(0x00FF0000);
		}
		if (i == 1400){
			r->unregister_object(om->get_object("boydown"));
			r->unregister_object(om->get_object("text2"));
		}
		if (i == 1500){
			break;
		}

		r->render();
		r->fps_regulate();
	}

	return 0;
}