#ifndef _FONT_RESOURCE_H_
#define _FONT_RESOURCE_H_

#define DEFAULT_FONT_SIZE 10

#include <SDL.h>
#include <SDL_ttf.h>
#include "Resource.h"

class FontResource : public Resource{
public:
	//�����
	TTF_Font* font;

	//���������� ������ ������
	unsigned int get_size();
	//������������� ����� ������ ������(!������ ����� ������������!)
	bool set_size(unsigned int size);

private:
	//��������� ��������� ��������� ���������
	friend ResourceManager;

	//������ ������
	unsigned int size;
	//���� � ����� �������
	std::string path;

	//��������� ������ �� �����, � ������������ ��������
	bool load_font(int newSize = -1);

	//��������� ������ �� ����� � ��������, ��������� � �����
	bool load(std::string path);
	//���� ����� �������� �������� �������� ����� ������������ �������
	bool unload();

	FontResource() {};
	~FontResource() {};
	FontResource(const FontResource&) {};
	FontResource& operator=(const FontResource&) {};
};

typedef FontResource FR;

#endif