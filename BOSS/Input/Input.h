#ifndef _INPUT_H_
#define _INPUT_H_

#include <string>
#include <map>
#include <SDL.h>
#include "../Lua/Lua.h"

class Input{
public:
	//������� ������������ ��������� ������
	static Input* init(Lua* lua);

	//������������ ������� key, ����� �������� � ������� � ����� path
	bool register_key(wchar_t key, std::string path);
	//true ���� ������� ������
	bool key_pressed(wchar_t key);

	//���������� ����(���������� �� �������� �����)
	bool handle();

private:
	//map ��� �������� ������ ������� �� key
	std::map<wchar_t, std::string> keyMap;

	//����� ������� � ������ ������ ������
	Uint8* keyStates;

	//lua
	Lua* lua;

	//�������� (�������� ��)
	Input() {};
	~Input();
	Input(const Input&) {};
	Input& operator=(const Input&) {};
};

#endif