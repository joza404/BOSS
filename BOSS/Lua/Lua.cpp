#include <iostream>
#include <luabind/luabind.hpp>

#include "Lua.h"

//������� ������������ ��������� ������
Lua* Lua::init()
{
	static Lua singleView;
	static bool classCreated = false;

	//���� ����� ��� ������
	if (classCreated == true) return &singleView;

	//�������������� Lua
	singleView.state = luaL_newstate();
    luaL_openlibs(singleView.state);

	//����������� � Luabind
	luabind::open(singleView.state);

#ifdef _DEBUG
	std::cout << "Lua ��������." << std::endl;
#endif

	classCreated = true;

	return &singleView;
}

//��������� ������
bool Lua::do_file(std::string path)
{
	if (this->state == nullptr)
		return false;

	luaL_dofile(this->state,path.c_str());

	return true;
}

//����������
Lua::~Lua()
{
	lua_close(state);

#ifdef _DEBUG
	std::cout << "Lua ��������." << std::endl;
#endif
}
