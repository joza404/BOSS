#include <iostream>
#include "AnimationObject.h"

//������� ����� ���������
bool AnimationObject::create_state(Resource* res, std::string u_name)
{
	if (res == 0){
#ifdef _DEBUG
		std::cout << "������. ������ ������� ����� ��������� ������� ��� �������." << std::endl;
#endif
		return false;
	}

	AnimationResource* ares = dynamic_cast<AnimationResource*>(res);
	if (ares == 0){
#ifdef _DEBUG
		std::cout << "������. �� ������� ������� ���������, �������� ��� �������." << std::endl;
#endif
		return false;
	}

	State* st = new State();
	st->res = ares;
	st->u_name = u_name;
	
	//��������� � map
	stateMap[u_name] = st;

	return true;
}

//������������� ����� ���������
bool AnimationObject::set_new_state(std::string u_name)
{
	try{
		//���� �� ������ - ������� ����������
		State* newSt = stateMap.at(u_name);
		
		//�������� ������� �����
		curStateName = u_name;
		//�������� ������ � ������ ������� � �����. � ����������
		h = newSt->res->image->h;
		w = newSt->res->image->w / newSt->res->frameCount;
		//��������� � ������ ������ ��������
		curAnimFrame = 0;
		x_offset = 0;
		//���� ������� �� ������ ������ ��������
		frameWait = newSt->res->frequency - 1;

		return true;
	}
	catch (...){
#ifdef _DEBUG
		std::cout << "������. �� ������� ��������� � ������ " << u_name << std::endl;
#endif
		return false;
	}
}

//���������� ������� ���������
AnimationObject::State* AnimationObject::get_current_state()
{
	return stateMap[curStateName];
}

//������� ������
bool AnimationObject::create(Resource* res)
{
	if (res == 0){
#ifdef _DEBUG
		std::cout << "������. �� ������� ������� ������, ����������� ������." << std::endl;
#endif
		return false;
	}

	AnimationResource* ares = dynamic_cast<AnimationResource*>(res);
	if (ares == 0){
#ifdef _DEBUG
		std::cout << "������. �� ������� ������� ������, �������� ��� �������." << std::endl;
#endif
		return false;
	}

	//�������������� ���� �������
	//������� ������ State � ������ "main"
	this->create_state(ares, DEFAULT_STATE_NAME);
	//������������� ������� state �� "main"
	this->set_new_state(DEFAULT_STATE_NAME);
	//�������������� ����������
	this->x = 0;
	this->y = 0;
	this->type = ObjectType::ANIMATION_OBJECT;

	return true;
}

//���� ����� �������� �������� �������� ����� ������������ �������
bool AnimationObject::destroy()
{
	//������� ��� ���������
	typedef std::map<std::string, State*>::iterator MI;
	for(MI i = stateMap.begin(); i != stateMap.end(); i++)
		delete i->second;

	return true;
}