#ifndef _INPUT_H_
#define _INPUT_H_

#include <string>
#include <map>
#include <SDL.h>
#include "../Lua/Lua.h"

class Input{
public:
	//singleton
	static Input& get_instance();

	bool register_key(wchar_t key, std::string path);
	bool key_pressed(wchar_t key) const;
	bool handle();

private:
	std::map<wchar_t, std::string> keyMap;
	Uint8* keyStates;
	Lua& lua;

	//hide it (singleton)
	Input(Lua& l) : lua(l) {}
	~Input() = default;
	Input() = delete;
	Input(const Input&) = delete;
	Input& operator=(const Input&) = delete;
};

//these functions are used for luaponte binding
bool bind_register_key(std::string, std::string);
bool bind_key_pressed(std::string);

#endif