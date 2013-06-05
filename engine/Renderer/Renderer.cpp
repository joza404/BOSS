#include "Renderer.h"
#include <SDL_ttf.h>
#include <SDL.h>

//local macroses (in .cpp)
#define WINDOW_SHOW_CURSOR 0

void Renderer::create_window(const std::string& caption, unsigned int width, unsigned int height,
					   unsigned int bitFormat, unsigned int FPS)
{
	params.caption = caption;
	params.w = width;
	params.h = height;
	params.FPS = FPS;
	params.bitFormat = bitFormat;

	//create window
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	screen = SDL_SetVideoMode(width, height, bitFormat, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption(caption.c_str(), NULL);
	SDL_ShowCursor(WINDOW_SHOW_CURSOR);
}

void Renderer::render()
{
	//iterate over all the layers
	for(auto& layer : layers){
		for(auto& animation : layer.animationSet){
			render_component(animation);
		}
		for(auto& image : layer.imageSet){
			render_component(image);
		}
		for(auto& text : layer.textSet){
			render_component(text);
		}
	}
	SDL_Flip(screen);
}

//regulate fps (main.cpp calls it)
void Renderer::fps_start()
{
	FPStimer = SDL_GetTicks();
}

void Renderer::fps_end()
{
	Uint32 deltaFPS = SDL_GetTicks() - FPStimer;

	if (deltaFPS < 1000 / params.FPS){
		SDL_Delay(1000 / params.FPS - deltaFPS);
	}
	FPStimer = SDL_GetTicks();
}

//resources call it from its constructors
void Renderer::set_color_key(AnimationResource* ares)
{
	Uint8 r, g, b;
	r = (ares->transColor >> 16) & 0x000000FF;
	g = (ares->transColor >> 8) & 0x000000FF;
	b = (ares->transColor) & 0x000000FF;

	SDL_SetColorKey(ares->image, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(screen->format, r, g, b));
}

void Renderer::convert_format(AnimationResource* ares)
{
	SDL_Surface* optimizedImage;
	optimizedImage = SDL_DisplayFormat(ares->image);
	SDL_FreeSurface(ares->image);
	ares->image = optimizedImage;
}

void Renderer::convert_format(ImageResource* ires)
{
	SDL_Surface* optimizedImage;
	optimizedImage = SDL_DisplayFormat(ires->image);
	SDL_FreeSurface(ires->image);
	ires->image = optimizedImage;
}

unsigned int Renderer::last_layer() const
{ 
	return RENDER_LAYER_AMOUNT - 1; 
}

//components call it
bool Renderer::register_component(Animation* anim, unsigned int layer)
{
	layers[layer].animationSet.insert(anim);
	return true;
}

bool Renderer::register_component(Image* img, unsigned int layer)
{
	layers[layer].imageSet.insert(img);
	return true;
}

bool Renderer::register_component(Text* text, unsigned int layer)
{
	layers[layer].textSet.insert(text);
	return true;
}

bool Renderer::unregister_component(Animation* anim, unsigned int layer)
{
	layers[layer].animationSet.erase(anim);
	return true;
}

bool Renderer::unregister_component(Image* img, unsigned int layer)
{
	layers[layer].imageSet.erase(img);
	return true;
}

bool Renderer::unregister_component(Text* text, unsigned int layer)
{
	layers[layer].textSet.erase(text);
	return true;
}

void Renderer::render_component(Animation* anim)
{
	Animation::Parameters params = anim->get_params();

	SDL_Rect image;
	image.x = params.sprite_x_offset;
	image.y = params.sprite_y_offset;
	image.w = params.w;
	image.h = params.h;

	SDL_Rect screen;
	screen.x = params.x;
	screen.y = params.y;

	SDL_BlitSurface(params.currentResource->image, &image, this->screen, &screen);
}

void Renderer::render_component(Image* img)
{
	Image::Parameters params = img->get_params();

	SDL_Rect image;
	image.x = 0;
	image.y = 0;
	image.w = params.w;
	image.h = params.h;

	SDL_Rect screen;
	screen.x = params.x;
	screen.y = params.y;

	SDL_BlitSurface(params.resource->image, &image, this->screen, &screen);
}

void Renderer::render_component(Text* text)
{
	Text::Parameters params = text->get_params();

	SDL_Rect image;
	image.x = 0;
	image.y = 0;
	image.w = params.w;
	image.h = params.h;

	SDL_Rect screen;
	screen.x = params.x;
	screen.y = params.y;

	SDL_BlitSurface(params.textSurface, &image, this->screen, &screen);
}