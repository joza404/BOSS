#include <iostream>
#include <SDL.h>

#include "Input.h"

//������� ������������ ��������� ������
Input* Input::init(Lua* lua)
{
	static Input singleView;
	static bool classCreated = false;

	//���� ����� ��� ������
	if (classCreated == true) return &singleView;

	singleView.lua = lua;

#ifdef _DEBUG
	std::cout << "Input ������� �������." << std::endl;
#endif

	classCreated = true;

	return &singleView;
}

//������������ ������� key, ����� �������� � ������� � ����� path
bool Input::register_key(wchar_t key, std::string path)
{
	keyMap[key] = path;

	return true;
}

//true ���� ������� ������
bool Input::key_pressed(wchar_t key)
{
	return keyStates[key];
}

//���������� ����(���������� �� �������� �����)
bool Input::handle()
{
	SDL_PumpEvents();
	keyStates = SDL_GetKeyState(nullptr);

	typedef std::map<wchar_t, std::string>::iterator IT;
	//�������� �� ���� ������������������ ��������
	for(IT it = keyMap.begin(); it != keyMap.end(); it++){
		//���� ������� ������
		if (keyStates[it->first] == true){
			lua->do_file(it->second);
		}
	}

	return true;
}

//����������
Input::~Input()
{
}