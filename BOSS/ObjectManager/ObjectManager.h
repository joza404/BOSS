#ifndef _OBJECT_MANAGER_H_
#define _OBJECT_MANAGER_H_

#include <map>

#include "Objects\Object.h"

class Object;

class ObjectManager{
public:
	//������� ������������ ��������� ������
	static ObjectManager* create_manager();
	//������� � ���� ��� ���������� ��� u_name
	Object* create_object(Resource* res, std::string u_name = "_set_my_name_to_default_lol_");
	//��������� ������ � ������ u_name �� ������
	bool destroy_object(std::string u_name);
	//��������� ������ � id == u_id �� ������
	bool destroy_object(unsigned int u_id);
	//��������� ������ obj �� ������
	bool destroy_object(Object* obj);
	
	//���������� ��������� �� ������ � ������ u_name
	Object* get_object(std::string u_name);
	//���������� ��������� �� ������ � id == u_id
	Object* get_object(unsigned int u_id);

private:
	//map ��� �������� ������ �� �����, ����� ������ ��������� �� ������
	std::map<std::string, Object*> nameMap;
	std::map<unsigned int, Object*> idMap;

	//������� ������ ������� ������������� ����� u_id
	static unsigned int u_id;
	inline unsigned int get_next_uid() {return u_id++;}

	//�������� (�������� ��)
	ObjectManager() {};
	~ObjectManager();
	ObjectManager(const ObjectManager&) {};
	ObjectManager& operator=(const ObjectManager&) {};
};

//�������� ��������
typedef ObjectManager OM;
#endif