#include <iostream>
#include "Renderer.h"

//создает единственный экземпляр класса
Renderer* Renderer::create_renderer(std::string windowCaption, int screenWidth, int screenHeight,
									int screenBitFormat, int FPS)
{
	static Renderer singleView;
	static bool classCreated = false;

	//если класс уже создан
	if (classCreated == true) return &singleView;


	//инициализируем настройки
	singleView.settings.caption = windowCaption;
	singleView.settings.w = screenWidth;
	singleView.settings.h = screenHeight;
	singleView.settings.bitFormat = screenBitFormat;
	singleView.settings.FPS = FPS;

	//создаем окно
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	singleView.screen = SDL_SetVideoMode(screenWidth, screenHeight, screenBitFormat , SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption(windowCaption.c_str(), NULL);
	SDL_ShowCursor(0);

	//по умолчанию создаем два слоя для рендеринга
	singleView.create_lay();
	singleView.create_lay();

	classCreated = true;

#ifdef _DEBUG
	std::cout << "Рендерер создан." << std::endl;
#endif

	return &singleView;
}

//вывод на экран
void Renderer::render()
{
	typedef std::vector<RenderLay*>::iterator VI;
	typedef std::set<Object*>::iterator SI;	
	RenderLay* curLay;
	//проходим по слоям
	for(VI i = layList.begin(); i != layList.end(); i++){
		curLay = *i;
		//проходим по объектам
		for(SI j = curLay->objSet.begin(); j != curLay->objSet.end(); j++){
			if ((*j)->type == ObjectType::IMAGE_OBJECT)
				render_object((ImageObject*)(*j)); else 
			if ((*j)->type == ObjectType::ANIMATION_OBJECT)
				render_object((AnimationObject*)(*j)); else
			if ((*j)->type == ObjectType::TEXT_OBJECT)
				render_object((TextObject*)(*j));
		}
	}

	//обновить экран
	SDL_Flip(screen);
}

//функция для регулировки fps(расположить в начале game loop)
void Renderer::fps_start()
{
	timerFPS = SDL_GetTicks();
}

//функция для регулировки fps(расположить в конце game loop)
void Renderer::fps_regulate()
{
	Uint32 deltaFPS = SDL_GetTicks() - timerFPS;

	if (deltaFPS < 1000 / settings.FPS){
		SDL_Delay(1000 / settings.FPS - deltaFPS);
	}

	timerFPS = SDL_GetTicks();
}

//задает цвет, который становится прозрачным (работает только с ресурсом анимацией)
void Renderer::set_key_color(Resource* res)
{
	AnimationResource* ares = dynamic_cast<AnimationResource*>(res);
	if (ares == 0){
#ifdef _DEBUG
		std::cout << "Ошибка. Не удалось установить прозрачный цвет, неверный тип ресурса." << std::endl;
#endif
		return;
	}

	Uint8 r, g, b;
	r = (ares->transColor >> 16) & 0x000000FF;
	g = (ares->transColor >> 8) & 0x000000FF;
	b = (ares->transColor) & 0x000000FF;

	SDL_SetColorKey(ares->image, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(screen->format, r, g, b));
}

//конвертирует ресурс изображение(или анимацию) в формат экрана
void Renderer::convert_format(Resource* res)
{
	SDL_Surface* optimizedImage;

	AnimationResource* ares = dynamic_cast<AnimationResource*>(res);
	if (ares != 0){
		//был передан ресурс - анимация
		optimizedImage = SDL_DisplayFormat(ares->image);
		SDL_FreeSurface(ares->image);
		ares->image = optimizedImage;
	} else {
		ImageResource* ires = dynamic_cast<ImageResource*>(res);
		if (ires != 0){
			//был передан ресурс - изображение
			optimizedImage = SDL_DisplayFormat(ires->image);
			SDL_FreeSurface(ires->image);
			ires->image = optimizedImage;
		} else {
#ifdef _DEBUG
			std::cout << "Ошибка. Не удалось конвертировать формат изображения, неверный тип ресурса." << std::endl;
#endif
		}
	}
}

//создает новый слой(автоматическая нумерация с нуля)
void Renderer::create_lay()
{
	//создаем слой
	RenderLay* rl = new RenderLay;

	//добавляем в список слоев
	layList.push_back(rl);
}

//уничтожает слой с номером i (объекты слоя перестают быть зареганами)
bool Renderer::destroy_lay(unsigned int i)
{
	//такого слоя нет
	if (i + 1 > layList.size()){
#ifdef _DEBUG
		std::cout << "Ошибка. Невозможно уничтожить слой " << i << " в виду его отсутствия" << std::endl;
#endif
		return false;
	}

	//удаляем слой из вектора, дорогостоящая операция
	std::vector<RenderLay*>::iterator it = layList.begin() + i;
	delete *it;
	layList.erase(it);

	return true;
}

//уничтожает все слои. все объекты перестают быть зарегистрированными
void Renderer::destroy_lays()
{
	//сначала уничтожаем все слои
	typedef std::vector<RenderLay*>::iterator LI;
	for (LI it = layList.begin(); it != layList.end(); it++)
		delete *it;
	
	//очищаем список слоев
	layList.clear();
}

//возвращает номер последнего слоя(если слой один то 0)
int Renderer::last_lay()
{
	return layList.size();
}

//регистрирует объект на рендеринг в слое layID
bool Renderer::register_object(Object* obj, unsigned int i_lay)
{
	if (obj == 0){
#ifdef _DEBUG
		std::cout << "Ошибка. Объект для регистрации на рендеринг не найден" << std::endl;
#endif
		return false;
	}

	if (i_lay + 1 > layList.size()){
#ifdef _DEBUG
		std::cout << "Ошибка. Объект не зарегистрирован, слоя "<< i_lay << " не существует" << std::endl;
#endif
		return false;
	}

	//регистрируем объект
	layList[i_lay]->objSet.insert(obj);

	return true;
}

//если layID не передали(т.е. -1, то проходит по всем слоям в поисках объекта)
bool Renderer::unregister_object(Object* obj, unsigned int i_lay)
{
	if (obj == 0){
#ifdef _DEBUG
		std::cout << "Ошибка. Объект для un_регистрации на рендеринг не найден" << std::endl;
#endif
		return false;
	}

	if (i_lay + 1 > layList.size()){
#ifdef _DEBUG
		std::cout << "Ошибка. Объект не un_регистрирован, слоя "<< i_lay << " не существует" << std::endl;
#endif
		return false;
	}

	if (i_lay != -1){
		//пользователь выбрал слой
		layList[i_lay]->objSet.erase(obj);
	} else {
		//пользователь не выбрал слой, идем по всем слоям
		typedef std::vector<RenderLay*>::iterator VI;
		for(VI i = layList.begin(); i != layList.end(); i++)
			(*i)->objSet.erase(obj);
	}

	return true;
}

//функция для рендеринга объекта - изображения
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

//функция для рендеринга объекта - анимации
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

	//ждем следующего фрейма
	if (obj->frameWait > 0){
		obj->frameWait--;
		return;
	}

	//смещаем x
	obj->x_offset += obj->w;
	obj->curAnimFrame++;
	if (obj->curAnimFrame == ares->frameCount){
		obj->x_offset = 0;
		obj->curAnimFrame = 0;
	}

	//отрисовали, сколько ждать до следующей рисовки
	obj->frameWait = ares->frequency - 1;
}

//функия для рендеринга объекта - шрифта
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
	std::cout << "Рендерер уничтожен." << std::endl;
#endif
}