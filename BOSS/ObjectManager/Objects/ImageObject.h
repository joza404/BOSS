#ifndef _IMAGE_OBJECT_H_
#define _IMAGE_OBJECT_H_

#include "Object.h"

class ImageObject : public Object{
public:
	//��������� �� ������ �������
	ImageResource* res;

	//�������� ������ �������
	unsigned int x_offset, y_offset;
	//������ � ������ ������ ��������� �����
	unsigned int w, h;
	//���������� ������� �� ������
	unsigned int x,y;

private:
	//��������� ��������� ��������� ���������
	friend ObjectManager;

	//������� ������
	bool create(Resource* res);
	//���� ����� �������� �������� �������� ����� ������������ �������
	bool destroy();

	ImageObject() {};
	~ImageObject() {};
	ImageObject(const ImageObject&) {};
	ImageObject& operator=(const ImageObject&) {};
};

typedef ImageObject IO;

#endif