#include <SDL.h>
#include "Input.h"

Input& Input::get_instance()
{
	static Input singleton;
	return singleton;
}

void Input::register_key(const std::string& str, const luaponte::object& function, int frequency)
{
	keyList.push_back( std::unique_ptr<InputKey>( new InputKey(str[0], function, frequency) ));
}

bool Input::key_pressed(const std::string& str) const
{
	return keyStates[str[0]];
}

void Input::update()
{
	SDL_PumpEvents();
	keyStates = SDL_GetKeyState(nullptr);

	static int frameToWait = updateFrequency;
	if (--frameToWait > 0) return;
	frameToWait = updateFrequency;

	//pressed keys handling
	for(auto& it : keyList){
		//if key is pressed
		if (keyStates[it->key] == 1){
			//if it's not first time
			if (it->prevPressed == true){
				if (it->frameToWait > 0) it->frameToWait--;
				else {
					it->function["Repeat"]();
					it->frameToWait = it->frequency - 1;
				}
			}
			//if first time pressed
			else{
				it->function["Press"]();
				it->frameToWait = it->frequency - 1;
				it->prevPressed = true;
			}
		}
		//if key is released
		else if (it->prevPressed == true){
			it->function["Release"]();
			it->prevPressed = false;
		}
	}
}
