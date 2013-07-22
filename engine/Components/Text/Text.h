#ifndef _TEXT_H_
#define _TEXT_H_

#include <memory>
#include <SDL.h>

#include "../BaseComponent.h"
#include "../../BaseObject.h"
#include "../../Resources/FontResource.h"
#include "../Position/Position.h"

class Text : public BaseComponent, public BaseObject{
public:
	//all Text parameters
	struct Parameters{
		SDL_Surface* textSurface = nullptr;
		FontResource* resource = nullptr;

		unsigned int renderLayer;
		bool regedInRenderer;

		std::string text;
		unsigned int size;
		SDL_Color color;

		bool textChanged;
		bool colorChanged;

		int x, y;
		unsigned int w, h;
	};
	//component update function
	void update();

	//set font resource
	void set_resource(FontResource& res);
	void set_resource(const std::string& res);

	//get/set render layer
	bool set_layer(unsigned int layer);
	unsigned int get_layer() const { return params.renderLayer; }

	//get/set text
	void set_text(const std::string& text);
	std::string get_text() const { return params.text; }

	//get/set color of 0x00RRGGBB format
	void set_color(int color);
	void set_color(SDL_Color color);
	int get_color() const;

	//returns a copy of current parameters
	Parameters get_params() const { return params; }

	//set references to other components
	void set_position(Position* pos) { positionComp = pos; }
	void set_position(const std::string& pos);
	void unset_position() { positionComp = nullptr; }

	Text(const std::string& name);
	~Text();
	Text() = delete;
	Text(const Text&) = delete;
	Text& operator=(const Text&) = delete;
	
private:
	Parameters params;

	//redraw surface using size, text, color
	bool redraw();

	//references to other components
	Position* positionComp = nullptr;
};

#endif