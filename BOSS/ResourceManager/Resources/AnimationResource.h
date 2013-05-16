#ifndef _ANIMATION_RESOURCE_H_
#define __ANIMATION_RESOURCE_H_

#include <SDL.h>
#include "Resource.h"

class AnimationResource : public Resource{
public:
	SDL_Surface* image;
	unsigned int frequency;
	unsigned int frameCount;
	int transColor;

private:
	//��������� ��������� ��������� ���������
	friend ResourceManager;

	//��������� ������
	bool load(std::string path);
	//���� ����� �������� �������� �������� ����� ������������ �������
	bool unload();

	AnimationResource() {frequency = frameCount = 0;};
	~AnimationResource() {};
	AnimationResource(const AnimationResource&) {};
	AnimationResource& operator=(const AnimationResource&) {};
};

typedef AnimationResource AR;

#endif