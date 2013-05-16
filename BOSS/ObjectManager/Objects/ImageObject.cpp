#include <iostream>
#include "ImageObject.h"
#include "..\..\ResourceManager\ResourceList.h"

//������� ������
bool ImageObject::create(Resource* res)
{
	if (res == 0){
#ifdef _DEBUG
		std::cout << "������. �� ������� ������� ������, ����������� ������." << std::endl;
#endif
		return false;
	}

	ImageResource* ires = dynamic_cast<ImageResource*>(res);
	if (ires == 0){
#ifdef _DEBUG
		std::cout << "������. �� ������� ������� ������, �������� ��� �������." << std::endl;
#endif
		return false;
	}

	//�������������� ���� �������
	this->res = ires;
	this->x_offset = 0;
	this->y_offset = 0;
	this->x = 0;
	this->y = 0;
	this->w = ires->image->w;
	this->h = ires->image->h;
	this->type = ObjectType::IMAGE_OBJECT;

	return true;
}

//���� ����� �������� �������� �������� ����� ������������ �������
bool ImageObject::destroy()
{
	//������ �� ������, �.�. ���� ������ ��� �������� �� �������� ������������ ������
	return true;
}