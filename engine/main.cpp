#include <locale>
#include <iostream>
#include <memory>

#include "globals.h"

#include "Input\Input.h"
#include "Resources\ResourceManager.h"
#include "Components\ComponentManager.h"
#include "Renderer\Renderer.h"
#include "Lua\Lua.h"


int main(int argc,char* argv[])
{
	setlocale(LC_ALL, "russian_russia.1251");
	TTF_Init();

	//renderer MUST be placed before component manager
	Renderer& renderer = Renderer::get_instance();
	ResourceManager& rm = ResourceManager::get_instance();
	ComponentManager& cm = ComponentManager::get_instance();
	Lua& lua = Lua::get_instance();
	Input& input = Input::get_instance();

	renderer.create_window(WINDOW_CAPTION, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_BIT_FORMAT, WINDOW_FPS);
	lua.bind_all();

	lua.do_file(LUA_INIT_SCRIPT);	

	cm.update_components();
	renderer.render();
	//game loop
	while (true){
		renderer.fps_start();
		input.handle();
		cm.update_components();
		renderer.render();
		renderer.fps_end();
	}
	
	return 0;
}