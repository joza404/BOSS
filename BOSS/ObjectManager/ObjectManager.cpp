#include <iostream>
#include "ObjectManager.h"
#include "ObjectList.h"

//��������� �������� u_id
unsigned int OM::u_id = 0;

//������� ������������ ��������� ������
OM* OM::create_manager()
{
	static OM singleView;

#ifdef _DEBUG
	std::cout << "�������� �������� ������." << std::endl;
#endif

	return &singleView;
}

Object* OM::create_object(Resource* res, std::string u_name)
{
	if (res == 0){
#ifdef _DEBUG
		std::cout << "������. �� ������� ������� ������, ����������� ������." << std::endl;
#endif
		return false;
	}

	Object* obj;
	//������� ������ ���� image
	if (res->type == ResourceType::IMAGE_RESOURCE){
		obj = new ImageObject();
		obj->type = ObjectType::IMAGE_OBJECT;
	} else
	if (res->type == ResourceType::ANIMATION_RESOURCE){
		obj = new AnimationObject();
		obj->type = ObjectType::ANIMATION_OBJECT;
	} else
	if (res->type == ResourceType::FONT_RESOURCE){
		obj = new TextObject();
		obj->type = ObjectType::TEXT_OBJECT;
	} else {
		//���� ������� �� ������� �� ����
		return 0;
	}

	//�������������� ������
	if (obj->create(res) == false){
		//���� �������� ������
		delete obj;
		return 0;
	}

	//������������� ���
	if (u_name != "_set_my_name_to_default_lol_")
		obj->u_name = u_name;
	else 
		obj->u_name = "_default_" + std::to_string(this->u_id) + "_";

	//������������� id
	obj->u_id = get_next_uid();

	//��������� map'�
	this->nameMap[obj->u_name] = obj;
	this->idMap[obj->u_id] = obj;

	return obj;
}

//��������� ������ � ������ u_name �� ������
bool OM::destroy_object(std::string u_name)
{
	try{
		//���� �� ������ - ������� ����������
		Object* obj = nameMap.at(u_name); 
		//������� �� map'��
		nameMap.erase(obj->u_name);
		idMap.erase(obj->u_id);

		obj->destroy();
		delete obj;

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
bool OM::destroy_object(unsigned int u_id)
{
	try{
		//���� �� ������ - ������� ����������
		Object* obj = idMap.at(u_id); 
		//������� �� map'��
		nameMap.erase(obj->u_name);
		idMap.erase(obj->u_id);

		obj->destroy();
		delete obj;

		return true;
	}
	catch (...){
#ifdef _DEBUG
		std::cout << "������. �� ������ ������ � id = " << u_id << std::endl;
#endif
		return false;
	}
}

//��������� ������ obj �� ������
bool OM::destroy_object(Object* obj)
{
	if (obj == 0)
		return false;

	nameMap.erase(obj->u_name);
	idMap.erase(obj->u_id);

	obj->destroy();
	delete obj;

	return true;
}

//���������� ��������� �� ������ � ������ u_name
Object* OM::get_object(std::string u_name)
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
Object* OM::get_object(unsigned int u_id)
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

ObjectManager::~ObjectManager()
{
	typedef std::map<unsigned int, Object*>::iterator MI;
	//����������� �������(�� �� ������� map'�, ��� ���� ����� �����������)
	for(MI i = idMap.begin(); i != idMap.end(); i++)
		i->second->destroy();

#ifdef _DEBUG
	std::cout << "�������� �������� ���������." << std::endl;
#endif
}