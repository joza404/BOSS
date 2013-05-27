#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <string>
#include "../ResourceManager/AnimationResource.h"
#include "../ResourceManager/ImageResource.h"
#include "../Components/Animation/Animation.h"
#include "../Components/Image/Image.h"

typedef unsigned int uint;

class Renderer{
public:
	//creates singleton
	static Renderer* get_instance(){
		static Renderer singleton;
		return &singleton;
	}
	
	void create_window(std::string windowCaption, uint screenWidth, uint screenHeight,
							  uint screenBitFormat, uint FPS);

	//render all the objects (main.cpp calls it)
	void render();

	//regulate fps (main.cpp calls it)
	void fps_start();
	void fps_end();

	//resources call it from its constructors
	void set_color_key(AnimationResource* );
	void convert_format(AnimationResource* );
	void convert_format(ImageResource* );

	//components call it 
	void create_lay(); //auto numeration from 0
	unsigned int last_lay();

	//components call it
	bool register_component(Animation*, unsigned int lay);
	bool register_component(Image*, unsigned int lay);
	bool unregister_component(Animation*, unsigned int lay);
	bool unregister_component(Image*, unsigned int lay);

private:
	struct Parameters{
		std::string caption;
		uint w;
		uint h;
		uint bitFormat;
		uint FPS;
	} params;

	//hide it(singleton)
	Renderer() {};
	~Renderer();
	Renderer(const Renderer&) {};
	Renderer& operator=(const Renderer&) {};
};

#endif