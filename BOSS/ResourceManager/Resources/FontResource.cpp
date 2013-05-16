#include <fstream>
#include <string>
#include <iostream>

#include "FontResource.h"
#include <SDL.h>

//���������� ������ ������
unsigned int FontResource::get_size()
{
	return this->size;
}

//������������� ����� ������ ������(!������ ����� ������������!)
bool FontResource::set_size(unsigned int size)
{
	//������� ��������� ������
	if(this->load_font(size)){
		this->size = size;
		return true;
	}

	return false;
}

//��������� ������
bool FontResource::load(std::string path)
{
	this->font = 0;
	this->path = path;

	//��������� ������ � �������� -1, ��� ������ "������ �� �����"
	return this->load_font();
}

bool FontResource::load_font(int newSize)
{
	std::ifstream file(path);
	if (file.good() == false){
#ifdef _DEBUG
		std::cout << "������. ���� � ������ " << path << " �� ������, ���� ���� ����, ���� ������ ��������" << std::endl;
#endif
		file.close();
		return false;
	}

	//������� ����, ������ ���������� ����������
	file.exceptions(std::istream::failbit | std::istream::badbit);
	std::string buff;
	try{
		file >> buff;
		if (buff != "FONT"){
#ifdef _DEBUG
			std::cout << "������. ������������ ������ info ����� �������: " << path << std::endl;
#endif
			file.close();
			return false;
		}
	
		//���� � ����� ������
		file >> buff;

		if (newSize < 0){
			//����� ������ �� �����
			file >> this->size;
		} else {
			//������������ ������� ������
			this->size = newSize;
		}
		//��������� �����
		TTF_Font* font = TTF_OpenFont(buff.c_str(), this->size);
		if (font == 0){
#ifdef _DEBUG
			std::cout << "������. �� ������� ��������� ����� � ������: " << buff << std::endl;
#endif
			file.close();
			return false;
		}

		//��������� ��������� �� �� ����� �� �����
		if (this->font != 0)
			TTF_CloseFont(this->font);
		this->font = font;
		this->type = ResourceType::FONT_RESOURCE;

#ifdef _DEBUG
		std::cout << "������ " << buff << " ��������" << std::endl;
#endif

		file.close();
		return true;
	}
	catch (...){
#ifdef _DEBUG
		std::cout << "������. ������������ ������ info ����� �������: " << path << std::endl;
#endif
		file.close();
		return false;
	}
}

//���� ����� �������� �������� �������� ����� ������������ �������
bool FontResource::unload()
{
	TTF_CloseFont(this->font);

	return true;
}