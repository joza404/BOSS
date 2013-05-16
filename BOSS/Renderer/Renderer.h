#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "../ResourceManager/ResourceList.h"
#include "../ObjectManager/ObjectList.h"
#include <string>
#include <set>
#include <list>
#include <vector>
#include <SDL.h>

class Resource;
class Object;

class Renderer{
public:
	//������� ������������ ��������� ������
	static Renderer* create_renderer(std::string windowCaption, int screenWidth, int screenHeight,
							  int screenBitFormat, int FPS);
	//����� �� ����� 
	void render();
	//������� ��� ����������� fps(����������� � ������ game loop)
	void fps_start();
	//������� ��� ����������� fps(����������� � ����� game loop)
	void fps_regulate();

	//������ ����, ������� ���������� ���������� (�������� ������ � �������� ���������)
	void set_key_color(Resource* res);
	//������������ ������ �����������(��� ��������) � ������ ������
	void convert_format(Resource* res);

	//������� ����� ����(�������������� ��������� � ����)
	void create_lay();
	//���������� ���� � ������� i (������� ���� ��������� ���� ����������)
	bool destroy_lay(unsigned int i);
	//���������� ��� ����. ��� ������� ��������� ���� �������������������
	void destroy_lays();
	//���������� ����� ���������� ����(���� ���� ���� �� 0)
	int last_lay();

	//������������ ������ �� ��������� � ���� i_lay
	bool register_object(Object* obj, unsigned int i_lay = 0);
	//���� i_lay �� ��������(�.�. -1, �� �������� �� ���� ����� � ������� �������)
	bool unregister_object(Object* obj, unsigned int i_lay = -1);

private:
	//��������� ������
	struct ScreenSettings{
		std::string caption;
		int w;
		int h;
		int bitFormat;
		int FPS;
	};
	ScreenSettings settings;

	//�����
	SDL_Surface* screen;

	//���� ��� ����������
	struct RenderLay{
		std::set<Object*> objSet;
	};
	std::vector<RenderLay*> layList;

	//������ ��� ����
	Uint32 timerFPS;

	//������� ��� ���������� ��������� ��������
	void render_object(ImageObject* obj);
	void render_object(AnimationObject* obj);
	void render_object(TextObject* obj);

	//�������� (�������� ��)
	Renderer() {};
	~Renderer();
	Renderer(const Renderer&) {};
	Renderer& operator=(const Renderer&) {};
};

#endif