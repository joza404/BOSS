#ifndef _INPUT_H_
#define _INPUT_H_

#include <string>
#include <map>
#include <SDL.h>
#include "../Lua/Lua.h"

class Input{
public:
	//создает единственный экземпл€р класса
	static Input* init(Lua* lua);

	//регистрируем клавишу key, набор действий в скрипте с путем path
	bool register_key(wchar_t key, std::string path);
	//true если клавиша нажата
	bool key_pressed(wchar_t key);

	//обработать ввод(вызываетс€ из главного цикла)
	bool handle();

private:
	//map дл€ быстрого поиска скрипта по key
	std::map<wchar_t, std::string> keyMap;

	//какие клавиши в данный момент нажаты
	Uint8* keyStates;

	//lua
	Lua* lua;

	//скрываем (синглтон же)
	Input() {};
	~Input();
	Input(const Input&) {};
	Input& operator=(const Input&) {};
};

#endif