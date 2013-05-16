#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_

#include <map>
#include <list>
#include <string>

#include "Resources\Resource.h"

class Resource;

class ResourceManager{
public:
	//������� ������������ ��������� ������
	static ResourceManager* create_manager();
	//��������� ������ �� ����� � ���� ��� ���������� ��� u_name
	Resource* load_resource(std::string path, std::string u_name = "_set_my_name_to_default_lol_");
	//��������� ������ � ������ u_name �� ������
	bool unload_resource(std::string u_name);
	//��������� ������ � id == u_id �� ������
	bool unload_resource(unsigned int u_id);
	//��������� ������ res �� ������
	bool unload_resource(Resource* res);
	
	//���������� ��������� �� ������ � ������ u_name
	Resource* get_resource(std::string u_name);
	//���������� ��������� �� ������ � id == u_id
	Resource* get_resource(unsigned int u_id);

private:
	//map ��� �������� ������ �� �����, ����� ������ ��������� �� ������
	std::map<std::string, Resource*> nameMap;
	std::map<unsigned int, Resource*> idMap;

	//������� ������ ������� ������������� ����� u_id
	static unsigned int u_id;
	inline unsigned int get_next_uid() {return u_id++;}

	//�������� (�������� ��)
	ResourceManager() {};
	~ResourceManager();
	ResourceManager(const ResourceManager&) {};
	ResourceManager& operator=(const ResourceManager&) {};
};

//�������� ��������
typedef ResourceManager RM;
#endif