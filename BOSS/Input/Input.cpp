#include <iostream>
#include <SDL.h>

#include "Input.h"

//создает единственный экземпляр класса
Input* Input::init(Lua* lua)
{
	static Input singleView;
	static bool classCreated = false;

	//если класс уже создан
	if (classCreated == true) return &singleView;

	singleView.lua = lua;

#ifdef _DEBUG
	std::cout << "Input система создана." << std::endl;
#endif

	classCreated = true;

	return &singleView;
}

//регистрируем клавишу key, набор действий в скрипте с путем path
bool Input::register_key(wchar_t key, std::string path)
{
	keyMap[key] = path;

	return true;
}

//true если клавиша нажата
bool Input::key_pressed(wchar_t key)
{
	return keyStates[key];
}

//обработать ввод(вызывается из главного цикла)
bool Input::handle()
{
	SDL_PumpEvents();
	keyStates = SDL_GetKeyState(nullptr);

	typedef std::map<wchar_t, std::string>::iterator IT;
	//проходим по всем зарегистрированным клавишам
	for(IT it = keyMap.begin(); it != keyMap.end(); it++){
		//если клавиша нажата
		if (keyStates[it->first] == true){
			lua->do_file(it->second);
		}
	}

	return true;
}

//деструктор
Input::~Input()
{
}