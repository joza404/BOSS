#include <fstream>
#include <string>
#include <iostream>

#include "AnimationResource.h"
#include <SDL.h>
#include <SDL_image.h>

//��������� ������
bool AnimationResource::load(std::string path)
{
	std::ifstream file(path);
	if (file.good() == false){
#ifdef _DEBUG
		std::cout << "������. ���� � ������ " << path << " �� ������, ���� ���� ����, ���� ������ ��������" << std::endl;
#endif
		file.close();
		return false;
	}

	file.exceptions(std::istream::failbit | std::istream::badbit);
	std::string buff;
	try{
		file >> buff;
		if (buff != "ANIMATION"){
	#ifdef _DEBUG
			std::cout << "������. ������������ ������ info ����� �������: " << path << std::endl;
	#endif
			file.close();
			return false;
		}

		//��������� �����������
		file >> buff;
		SDL_Surface* surface = IMG_Load(buff.c_str());
		if (surface == 0){
#ifdef _DEBUG
			std::cout << "������. ������������ ������ ����� �������: " << buff << std::endl;
#endif
			file.close();
			return false;
		}

		//��������� ��������� ��������
		file >> this->frequency;
		file >> this->frameCount;
		file >> std::hex >> this->transColor;
		
		//�������� ��������� �������
		this->image = surface;
		this->type = ResourceType::ANIMATION_RESOURCE;

#ifdef _DEBUG
		std::cout << "������ " << buff << " ��������" << std::endl;
#endif

		file.close();
		return true;
	}
	catch (...) {
#ifdef _DEBUG
		std::cout << "������. ������������ ������ info ����� �������: " << path << std::endl;
#endif
		file.close();
		return false;
	}

}

//���� ����� �������� �������� �������� ����� ������������ �������
bool AnimationResource::unload()
{
	SDL_FreeSurface(this->image);

	return true;
}