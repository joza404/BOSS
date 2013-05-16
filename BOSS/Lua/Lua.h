#ifndef _LUA_H_
#define _LUA_H_

#include <string>
#include <lua.hpp>

class Lua{
public:
	//������� ������������ ��������� ������
	static Lua* init();

	//��������� ������
	bool do_file(std::string path);

private:
	//����������� 
	lua_State* state;

	//�������� (�������� ��)
	Lua() {};
	~Lua();
	Lua(const Lua&) {};
	Lua& operator=(const Lua&) {};
};

#endif