#include "ResourceManager.h"
#include "ResourceList.h"
#include <iostream>
#include <fstream>

//��������� �������� u_id
unsigned int RM::u_id = 0;

//������� ������������ ��������� ������
RM* RM::create_manager()
{
	static RM singleView;

#ifdef _DEBUG
	std::cout << "�������� �������� ������." << std::endl;
#endif

	return &singleView;
}

//��������� ������ �� ����� � ���� ��� ���������� ��� u_name
Resource* RM::load_resource(std::string path, std::string u_name)
{

	std::ifstream file(path);
	if (file.good() == false){
#ifdef _DEBUG
		std::cout << "������. ���� � ������ " << path << " �� ������, ���� ���� ����, ���� ������ ��������" << std::endl;
#endif
		file.close();
		return 0;
	}

	//������� ����, ������ ���������� ����������
	file.exceptions(std::istream::failbit | std::istream::badbit);
	std::string buff;
	try{
		file >> buff;
	}
	catch (...){
#ifdef _DEBUG
		std::cout << "������. ������������ ������ info ����� �������: " << path << std::endl;
#endif
		file.close();
		return 0;
	}
	file.close();

	Resource* res;

	if (buff == "IMAGE"){
		res = new ImageResource();
		res->type = ResourceType::IMAGE_RESOURCE;
	} else 
	if (buff == "ANIMATION"){
		res = new AnimationResource();
		res->type = ResourceType::ANIMATION_RESOURCE;
	} else 
	if (buff == "FONT"){
		res = new FontResource();
		res->type = ResourceType::FONT_RESOURCE;
	} else {
#ifdef _DEBUG
		std::cout << "������. �������� ������ info ����� �������: " << path << std::endl;
#endif
		return 0;
	}

	if (res->load(path) == false){
		//���� �������� ������
		delete res;
		return 0;
	}

	//������������� ���
	if (u_name != "_set_my_name_to_default_lol_")
		res->u_name = u_name;
	else 
		res->u_name = "_default_" + std::to_string(this->u_id) + "_";

	//������������� id
	res->u_id = get_next_uid();

	//��������� map'�
	this->nameMap[res->u_name] = res;
	this->idMap[res->u_id] = res;

	return res;
}

//��������� ������ � ������ u_name �� ������
bool RM::unload_resource(std::string u_name)
{
	try{
		//���� �� ������ - ������� ����������
		Resource* res = nameMap.at(u_name); 
		//������� �� map'��
		nameMap.erase(res->u_name);
		idMap.erase(res->u_id);

		res->unload();
		delete res;

		return true;
	}
	catch (...){
#ifdef _DEBUG
		std::cout << "������. �� ������ ������ � ������ " << u_name << std::endl;
#endif
		return false;
	}
}

//��������� ������ � id == u_id �� ������
bool RM::unload_resource(unsigned int u_id)
{
	try{
		//���� �� ������ - ������� ����������
		Resource* res = idMap.at(u_id); 
		//������� �� map'��
		nameMap.erase(res->u_name);
		idMap.erase(res->u_id);

		res->unload();
		delete res;

		return true;
	}
	catch (...){
#ifdef _DEBUG
		std::cout << "������. �� ������ ������ � id = " << u_id << std::endl;
#endif
		return false;
	}
}

//��������� ������ res �� ������
bool RM::unload_resource(Resource* res)
{
	if (res == 0)
		return false;

	nameMap.erase(res->u_name);
	idMap.erase(res->u_id);

	res->unload();
	delete res;

	return true;
}

//���������� ��������� �� ������ � ������ u_name
Resource* RM::get_resource(std::string u_name)
{
	try{
		//���� �� ������ - ������� ����������
		return nameMap.at(u_name);
	}
	catch (...){
#ifdef _DEBUG
		std::cout << "������. �� ������ ������ � ������ " << u_name << std::endl;
#endif
		return 0;
	}
}

//���������� ��������� �� ������ � id == u_id
Resource* RM::get_resource(unsigned int u_id)
{
	try{
		//���� �� ������ - ������� ����������
		return idMap.at(u_id);
	}
	catch (...){
#ifdef _DEBUG
		std::cout << "������. �� ������ ������ � id = " << u_id << std::endl;
#endif
		return 0;
	}
}

ResourceManager::~ResourceManager()
{
	typedef std::map<unsigned int, Resource*>::iterator MI;
	//����������� �������(�� �� ������� map'�, ��� ���� ����� �����������)
	for(MI i = idMap.begin(); i != idMap.end(); i++)
		i->second->unload();

#ifdef _DEBUG
	std::cout << "�������� �������� ���������." << std::endl;
#endif
}