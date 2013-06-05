#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <string>
#include <set>
#include <array>

#include <SDL.h>

#include "../ResourceManager/AnimationResource.h"
#include "../ResourceManager/ImageResource.h"
#include "../Components/Animation/Animation.h"
#include "../Components/Image/Image.h"
#include "../Components/Text/Text.h"

//global macroses (in .h)
#define RENDER_LAYER_AMOUNT 10

class Renderer{
public:
	//creates singleton
	static Renderer* get_instance(){
		static Renderer singleton;
		return &singleton;
	}
	
	void create_window(const std::string& caption, unsigned int width, unsigned int height,
					   unsigned int bitFormat, unsigned int FPS);

	//render all the objects (main.cpp calls it)
	void render();

	//regulate fps (main.cpp calls it)
	void fps_start();
	void fps_end();

	//resources call it from its constructors
	void set_color_key(AnimationResource*);
	void convert_format(AnimationResource*);
	void convert_format(ImageResource*);

	unsigned int last_layer() const;

	//components call it
	bool register_component(Animation*, unsigned int layer);
	bool register_component(Image*, unsigned int layer);
	bool register_component(Text*, unsigned int layer);
	bool unregister_component(Animation*, unsigned int layer);
	bool unregister_component(Image*, unsigned int layer);
	bool unregister_component(Text*, unsigned int layer);

private:
	struct WindowParameters{
		std::string caption;
		unsigned int w;
		unsigned int h;
		unsigned int bitFormat;
		unsigned int FPS;
	} params;

	SDL_Surface* screen;
	//timer for fps regulating
	Uint32 FPStimer;

	struct RenderLayer{
		std::set<Animation*> animationSet;
		std::set<Image*> imageSet;
		std::set<Text*> textSet;
	};
	std::array<RenderLayer, RENDER_LAYER_AMOUNT> layers;

	void render_component(Animation*);
	void render_component(Image*);
	void render_component(Text*);

	//hide it(singleton)
	Renderer() = default;
	~Renderer() = default;
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
};

#endif