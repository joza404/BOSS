#include <iostream>
#include "Renderer.h"

//������� ������������ ��������� ������
Renderer* Renderer::create_renderer(std::string windowCaption, int screenWidth, int screenHeight,
									int screenBitFormat, int FPS)
{
	static Renderer singleView;
	static bool classCreated = false;

	//���� ����� ��� ������
	if (classCreated == true) return &singleView;


	//�������������� ���������
	singleView.settings.caption = windowCaption;
	singleView.settings.w = screenWidth;
	singleView.settings.h = screenHeight;
	singleView.settings.bitFormat = screenBitFormat;
	singleView.settings.FPS = FPS;

	//������� ����
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	singleView.screen = SDL_SetVideoMode(screenWidth, screenHeight, screenBitFormat , SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption(windowCaption.c_str(), NULL);
	SDL_ShowCursor(0);

	//�� ��������� ������� ��� ���� ��� ����������
	singleView.create_lay();
	singleView.create_lay();

	classCreated = true;

#ifdef _DEBUG
	std::cout << "�������� ������." << std::endl;
#endif

	return &singleView;
}

//����� �� �����
void Renderer::render()
{
	typedef std::vector<RenderLay*>::iterator VI;
	typedef std::set<Object*>::iterator SI;	
	RenderLay* curLay;
	//�������� �� �����
	for(VI i = layList.begin(); i != layList.end(); i++){
		curLay = *i;
		//�������� �� ��������
		for(SI j = curLay->objSet.begin(); j != curLay->objSet.end(); j++){
			if ((*j)->type == ObjectType::IMAGE_OBJECT)
				render_object((ImageObject*)(*j)); else 
			if ((*j)->type == ObjectType::ANIMATION_OBJECT)
				render_object((AnimationObject*)(*j)); else
			if ((*j)->type == ObjectType::TEXT_OBJECT)
				render_object((TextObject*)(*j));
		}
	}

	//�������� �����
	SDL_Flip(screen);
}

//������� ��� ����������� fps(����������� � ������ game loop)
void Renderer::fps_start()
{
	timerFPS = SDL_GetTicks();
}

//������� ��� ����������� fps(����������� � ����� game loop)
void Renderer::fps_regulate()
{
	Uint32 deltaFPS = SDL_GetTicks() - timerFPS;

	if (deltaFPS < 1000 / settings.FPS){
		SDL_Delay(1000 / settings.FPS - deltaFPS);
	}

	timerFPS = SDL_GetTicks();
}

//������ ����, ������� ���������� ���������� (�������� ������ � �������� ���������)
void Renderer::set_key_color(Resource* res)
{
	AnimationResource* ares = dynamic_cast<AnimationResource*>(res);
	if (ares == 0){
#ifdef _DEBUG
		std::cout << "������. �� ������� ���������� ���������� ����, �������� ��� �������." << std::endl;
#endif
		return;
	}

	Uint8 r, g, b;
	r = (ares->transColor >> 16) & 0x000000FF;
	g = (ares->transColor >> 8) & 0x000000FF;
	b = (ares->transColor) & 0x000000FF;

	SDL_SetColorKey(ares->image, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(screen->format, r, g, b));
}

//������������ ������ �����������(��� ��������) � ������ ������
void Renderer::convert_format(Resource* res)
{
	SDL_Surface* optimizedImage;

	AnimationResource* ares = dynamic_cast<AnimationResource*>(res);
	if (ares != 0){
		//��� ������� ������ - ��������
		optimizedImage = SDL_DisplayFormat(ares->image);
		SDL_FreeSurface(ares->image);
		ares->image = optimizedImage;
	} else {
		ImageResource* ires = dynamic_cast<ImageResource*>(res);
		if (ires != 0){
			//��� ������� ������ - �����������
			optimizedImage = SDL_DisplayFormat(ires->image);
			SDL_FreeSurface(ires->image);
			ires->image = optimizedImage;
		} else {
#ifdef _DEBUG
			std::cout << "������. �� ������� �������������� ������ �����������, �������� ��� �������." << std::endl;
#endif
		}
	}
}

//������� ����� ����(�������������� ��������� � ����)
void Renderer::create_lay()
{
	//������� ����
	RenderLay* rl = new RenderLay;

	//��������� � ������ �����
	layList.push_back(rl);
}

//���������� ���� � ������� i (������� ���� ��������� ���� ����������)
bool Renderer::destroy_lay(unsigned int i)
{
	//������ ���� ���
	if (i + 1 > layList.size()){
#ifdef _DEBUG
		std::cout << "������. ���������� ���������� ���� " << i << " � ���� ��� ����������" << std::endl;
#endif
		return false;
	}

	//������� ���� �� �������, ������������� ��������
	std::vector<RenderLay*>::iterator it = layList.begin() + i;
	delete *it;
	layList.erase(it);

	return true;
}

//���������� ��� ����. ��� ������� ��������� ���� �������������������
void Renderer::destroy_lays()
{
	//������� ���������� ��� ����
	typedef std::vector<RenderLay*>::iterator LI;
	for (LI it = layList.begin(); it != layList.end(); it++)
		delete *it;
	
	//������� ������ �����
	layList.clear();
}

//���������� ����� ���������� ����(���� ���� ���� �� 0)
int Renderer::last_lay()
{
	return layList.size();
}

//������������ ������ �� ��������� � ���� layID
bool Renderer::register_object(Object* obj, unsigned int i_lay)
{
	if (obj == 0){
#ifdef _DEBUG
		std::cout << "������. ������ ��� ����������� �� ��������� �� ������" << std::endl;
#endif
		return false;
	}

	if (i_lay + 1 > layList.size()){
#ifdef _DEBUG
		std::cout << "������. ������ �� ���������������, ���� "<< i_lay << " �� ����������" << std::endl;
#endif
		return false;
	}

	//������������ ������
	layList[i_lay]->objSet.insert(obj);

	return true;
}

//���� layID �� ��������(�.�. -1, �� �������� �� ���� ����� � ������� �������)
bool Renderer::unregister_object(Object* obj, unsigned int i_lay)
{
	if (obj == 0){
#ifdef _DEBUG
		std::cout << "������. ������ ��� un_����������� �� ��������� �� ������" << std::endl;
#endif
		return false;
	}

	if (i_lay + 1 > layList.size()){
#ifdef _DEBUG
		std::cout << "������. ������ �� un_�������������, ���� "<< i_lay << " �� ����������" << std::endl;
#endif
		return false;
	}

	if (i_lay != -1){
		//������������ ������ ����
		layList[i_lay]->objSet.erase(obj);
	} else {
		//������������ �� ������ ����, ���� �� ���� �����
		typedef std::vector<RenderLay*>::iterator VI;
		for(VI i = layList.begin(); i != layList.end(); i++)
			(*i)->objSet.erase(obj);
	}

	return true;
}

//������� ��� ���������� ������� - �����������
void Renderer::render_object(ImageObject* obj)
{
	SDL_Rect image;
	SDL_Rect screen;

	image.x = obj->x_offset;
	image.y = obj->y_offset;
	image.w = obj->w;
	image.h = obj->h;
	screen.x = obj->x;
	screen.y = obj->y;

	SDL_BlitSurface(obj->res->image, &image, this->screen, &screen);
}

//������� ��� ���������� ������� - ��������
void Renderer::render_object(AnimationObject* obj)
{
	SDL_Rect image;
	SDL_Rect screen;

	image.x = obj->x_offset;
	image.y = 0;
	image.w = obj->w;
	image.h = obj->h;
	screen.x = obj->x;
	screen.y = obj->y;

	AnimationResource* ares = obj->get_current_state()->res;

	SDL_BlitSurface(ares->image, &image, this->screen, &screen);

	//���� ���������� ������
	if (obj->frameWait > 0){
		obj->frameWait--;
		return;
	}

	//������� x
	obj->x_offset += obj->w;
	obj->curAnimFrame++;
	if (obj->curAnimFrame == ares->frameCount){
		obj->x_offset = 0;
		obj->curAnimFrame = 0;
	}

	//����������, ������� ����� �� ��������� �������
	obj->frameWait = ares->frequency - 1;
}

//������ ��� ���������� ������� - ������
void Renderer::render_object(TextObject* obj)
{
	SDL_Rect image;
	SDL_Rect screen;

	image.x = 0;
	image.y = 0;
	image.w = obj->image->w;
	image.h = obj->image->h;
	screen.x = obj->x;
	screen.y = obj->y;

	SDL_BlitSurface(obj->image, &image, this->screen, &screen);
}

Renderer::~Renderer()
{
	destroy_lays();

#ifdef _DEBUG
	std::cout << "�������� ���������." << std::endl;
#endif
}