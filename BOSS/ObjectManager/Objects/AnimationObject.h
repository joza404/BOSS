#ifndef _ANIMATION_OBJECT_H_
#define _ANIMATION_OBJECT_H_

#define DEFAULT_STATE_NAME "main"

#include "Object.h"
#include <map>
#include <string>

class AnimationObject : public Object{
public:
	//� ������������� ������� ���� ������ "���������" (�������� - ����� �����\������)
	struct State{
		AnimationResource* res;
		std::string u_name;
	};

	//������ � ������ ������ ��������� �����
	unsigned int w, h;
	//���������� ������� �� ������
	unsigned int x,y;

	//������� ����� �������� (��� ������� � ������)
	unsigned int curAnimFrame;
	//��������
	unsigned int x_offset;
	//������� ����� ��� ��������� �������, ����� ����������� ����� �������� (��� �������)
	unsigned int frameWait;

	//������� ����� ���������
	bool create_state(Resource* res, std::string u_name);
	//������������� ����� ���������
	bool set_new_state(std::string u_name);
	//���������� ������� ���������
	State* get_current_state();

private:
	//��������� ��������� ��������� ���������
	friend ObjectManager;

	//map ���� ���������
	std::map<std::string, State*> stateMap;
	//��� �������� ���������
	std::string curStateName;

	//������� ������
	bool create(Resource* res);
	//���� ����� �������� �������� �������� ����� ������������ �������
	bool destroy();

	AnimationObject() {};
	~AnimationObject() {};
	AnimationObject(const AnimationObject&) {};
	AnimationObject& operator=(const AnimationObject&) {};
};

//�������� ��������
typedef AnimationObject AO;

#endif