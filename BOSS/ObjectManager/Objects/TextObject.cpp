#include <iostream>
#include "TextObject.h"
#include "..\..\ResourceManager\ResourceList.h"

//������������� ����� ����� ��������� ������
bool TextObject::set_text(std::string text)
{
	if (text.size() == 0){
#ifdef _DEBUG
		std::cout << "������. ������ �������� ������ ������!" << std::endl;
#endif
		return false;
	}

	this->text = text;
	this->create_image();

	return true;
}

//���������� ����� 
std::string TextObject::get_text()
{
	return this->text;
}

bool TextObject::set_size(unsigned int size)
{
	bool check = this->res->set_size(size);
	return check & create_image();
}
unsigned int TextObject::get_size()
{
	return this->res->get_size();
}

//������������� ���� ������ � ������� 0x00RRGGBB
bool TextObject::set_color(int color)
{
	this->color.r = (color >> 16) & 0x000000FF;
	this->color.g = (color >>  8) & 0x000000FF;
	this->color.b = (color	    ) & 0x000000FF;

	return this->create_image();
}

//���������� ����
int TextObject::get_color()
{
	return ((int)color.r << 16) | ((int)color.g << 8) | ((int)color.b) ;
}

//������� ����������� �� ������ font, text, color
bool TextObject::create_image()
{
	//������� �� ������ ���
	if (this->image != 0)
		SDL_FreeSurface(this->image);

	image = TTF_RenderText_Solid(this->res->font, this->text.c_str(), this->color);
	//false ���� ����������� �� ���� �������
	return (image != 0);
}

//������� ������
bool TextObject::create(Resource* res)
{
	if (res == 0){
#ifdef _DEBUG
		std::cout << "������. �� ������� ������� ������, ����������� ������." << std::endl;
#endif
		return false;
	}

	FontResource*fres = dynamic_cast<FontResource*>(res);
	if (fres == 0){
#ifdef _DEBUG
		std::cout << "������. �� ������� ������� ������, �������� ��� �������." << std::endl;
#endif
		return false;
	}

	//�������������� ���� �������
	this->image = 0;
	this->x = 0;
	this->y = 0;
	this->res = fres;
	this->text = DEFAULT_TEXT;
	this->type = ObjectType::TEXT_OBJECT;
	return this->set_color(DEFAULT_COLOR);
}

//���� ����� �������� �������� �������� ����� ������������ �������
bool TextObject::destroy()
{
	SDL_FreeSurface(this->image);

	return true;
}