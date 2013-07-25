#ifndef _INPUT_H_
#define _INPUT_H_

#include <string>
#include <SDL.h>
#include <list>
#include <memory>
#include <luaponte\luaponte.hpp>
#include <luaponte\object.hpp>

#define DEFAULT_INPUT_UPDATE_FREQUENCY 1

class Input{
public:
	//singleton
	static Input& get_instance();

	void register_key(const std::string&, const luaponte::object&, int);
	bool key_pressed(const std::string&) const;
	int set_update_frequency(int f) { updateFrequency = f; }
	void update();

private:
	struct InputKey{
		const char key;
		const luaponte::object function;
		bool prevPressed = false;
		int frameToWait = 1;
		const int frequency;

		InputKey(const char _key, const luaponte::object& _func, int _fr) : key(_key), function(_func), frequency(_fr) {} 
	};

	//using ptrs to blow over the move semantics (too lazy)
	std::list< std::unique_ptr<InputKey> > keyList;
	Uint8* keyStates = nullptr;
	int updateFrequency = DEFAULT_INPUT_UPDATE_FREQUENCY;

	//hide it (singleton)
	Input() = default;
	~Input() = default;
	Input(const Input&) = delete;
	Input& operator=(const Input&) = delete;
};

#endif