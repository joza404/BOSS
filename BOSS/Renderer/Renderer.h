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
	//создает единственный экземпл€р класса
	static Renderer* create_renderer(std::string windowCaption, int screenWidth, int screenHeight,
							  int screenBitFormat, int FPS);
	//вывод на экран 
	void render();
	//функци€ дл€ регулировки fps(расположить в начале game loop)
	void fps_start();
	//функци€ дл€ регулировки fps(расположить в конце game loop)
	void fps_regulate();

	//задает цвет, который становитс€ прозрачным (работает только с ресурсом анимацией)
	void set_key_color(Resource* res);
	//конвертирует ресурс изображение(или анимацию) в формат экрана
	void convert_format(Resource* res);

	//создает новый слой(автоматическа€ нумераци€ с нул€)
	void create_lay();
	//уничтожает слой с номером i (объекты сло€ перестают быть зареганами)
	bool destroy_lay(unsigned int i);
	//уничтожает все слои. все объекты перестают быть зарегистрированными
	void destroy_lays();
	//возвращает номер последнего сло€(если слой один то 0)
	int last_lay();

	//регистрирует объект на рендеринг в слое i_lay
	bool register_object(Object* obj, unsigned int i_lay = 0);
	//если i_lay не передали(т.е. -1, то проходит по всем сло€м в поисках объекта)
	bool unregister_object(Object* obj, unsigned int i_lay = -1);

private:
	//настройки экрана
	struct ScreenSettings{
		std::string caption;
		int w;
		int h;
		int bitFormat;
		int FPS;
	};
	ScreenSettings settings;

	//экран
	SDL_Surface* screen;

	//слой дл€ рендеринга
	struct RenderLay{
		std::set<Object*> objSet;
	};
	std::vector<RenderLay*> layList;

	//таймер дл€ фпса
	Uint32 timerFPS;

	//функции дл€ рендеринга различных объектов
	void render_object(ImageObject* obj);
	void render_object(AnimationObject* obj);
	void render_object(TextObject* obj);

	//скрываем (синглтон же)
	Renderer() {};
	~Renderer();
	Renderer(const Renderer&) {};
	Renderer& operator=(const Renderer&) {};
};

#endif