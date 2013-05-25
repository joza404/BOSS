#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <SDL.h>
#include "..\ResourceManager\AnimationResource.h""


class Renderer{
public:
	//creates singleton
	static Renderer* init(std::string windowCaption, int screenWidth, int screenHeight,
							  int screenBitFormat, int FPS);

	//regulate fps (put this on the start of game loop)
	void fps_start();
	//regulate fps (put this on the end of game loop)
	void fps_regulate();

	void set_key_color(AnimationResource* res);
	void convert_format(AnimationResource* res);

private:
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

	//таймер для фпса
	Uint32 timerFPS;

	//hide it
	Renderer() {};
	~Renderer();
	Renderer(const Renderer&) {};
	Renderer& operator=(const Renderer&) {};
};

#endif