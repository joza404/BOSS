#ifndef _TEXT_OBJECT_H
#define _TEXT_OBJECT_H

#define DEFAULT_TEXT "DEFAULT"
#define DEFAULT_COLOR 0x00FFFFFF

#include "Object.h"
#include <SDL.h>

class TextObject : public Object{
public:
	//��������� �� ������ ������
	FontResource* res;
	//��� ����� �������� surface ������
	SDL_Surface* image;

	//���������� ������� �� ������
	unsigned int x,y;

	//������������� ����� ����� ��������� ������
	bool set_text(std::string text);
	//���������� ����� 
	std::string get_text();
	bool set_size(unsigned int size);
	unsigned int get_size();
	//������������� ���� ������ � ������� 0x00RRGGBB
	bool set_color(int color);
	//���������� ����
	int get_color();

private:
	//��������� ��������� ��������� ���������
	friend ObjectManager;

	//�����
	std::string text;
	//���� ������
	SDL_Color color;

	//������� ����������� �� ������ font, text, color
	bool create_image();

	//������� ������
	bool create(Resource* res);
	//���� ����� �������� �������� �������� ����� ������������ �������
	bool destroy();

	TextObject() {};
	~TextObject() {};
	TextObject(const TextObject&) {};
	TextObject& operator=(const TextObject&) {};
};

//�������� ��������
typedef TextObject TO;

#endif