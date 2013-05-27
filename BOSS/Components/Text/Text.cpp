#include "Text.h"
#include "../../ResourceManager/FontResource.h"
#include "../../ResourceManager/ResourceManager.h"
#include "../../Renderer/Renderer.h"
#include "../ComponentManager.h"

//local macroses (in .cpp)
#define DEFAULT_RENDER_LAYER 1
#define DEFAULT_X 0
#define DEFAULT_Y 0
#define DEFAULT_COLOR 0x000000FF

//component update function
void Text::update()
{
	//redraw surface
	if (params.colorChanged || params.textChanged){
		params.colorChanged = false;
		params.textChanged = false;
		redraw();
	}

	//if position component exists
	if (positionComp.expired() == false){
		auto shared = positionComp.lock();
		params.x = shared->get_x();
		params.y = shared->get_y();
	}
}

void Text::set_resource(const std::shared_ptr<FontResource>& res)
{
	params.resource = res;
	params.size = res->size;

	//first time here
	if (params.regedInRenderer == false){
		Renderer::get_instance()->register_component(this, params.renderLayer);
		params.regedInRenderer = true;
	}
}

void Text::set_resource(const std::string& res)
{
	auto& resource = ResourceManager::get_instance()->get_resource<FontResource>(res);
	params.resource = resource;
	params.size = resource->size;

	//first time here
	if (params.regedInRenderer == false){
		Renderer::get_instance()->register_component(this, params.renderLayer);
		params.regedInRenderer = true;
	}
}

bool Text::set_layer(unsigned int layer)
{
	Renderer* renderer = Renderer::get_instance();
	if (renderer->last_layer() > layer)
		return false;

	params.renderLayer = layer;
	//if registred in render
	if (params.regedInRenderer == true){
		renderer->unregister_component(this, params.renderLayer);
		renderer->register_component(this, layer);
	}	
	return true;
}

void Text::set_text(const std::string& text)
{
	params.text = text;
	params.textChanged = true;
}

void Text::set_color(int color)
{
	params.color.r = (color >> 16) & 0x000000FF;
	params.color.g = (color >>  8) & 0x000000FF;
	params.color.b = (color	    ) & 0x000000FF;
	params.colorChanged = true;
}

void Text::set_color(SDL_Color color)
{
	params.color = color;
	params.colorChanged = true;
}

int Text::get_color() const
{
	int color = 0;
	color = color | (params.color.g << 16);
	color = color | (params.color.g << 8);
	color = params.color.b;
	return color;
}
bool Text::redraw()
{
	if (params.regedInRenderer == false) return false;

	if (params.textSurface != nullptr){ 
		SDL_FreeSurface(params.textSurface);
	}
	params.textSurface = TTF_RenderText_Solid(params.resource->font, params.text.c_str(), params.color);
	if (params.textSurface == nullptr) return false;

	params.w = params.textSurface->w;
	params.h = params.textSurface->h;
	return (params.textSurface != 0);
}

void Text::set_position(const std::string& pos)
{
	positionComp = ComponentManager::get_instance()->get_component<Position>(pos);
}

Text::Text(const std::string& _name, const unsigned int _id) : BaseObject(_name, _id)
{
	params.renderLayer = DEFAULT_RENDER_LAYER;
	params.x = DEFAULT_X;
	params.y = DEFAULT_Y;
	set_color(DEFAULT_COLOR);
	params.text = _name;
	params.colorChanged = false;
	params.textChanged = false;
	params.h = params.w = 0;
	params.textSurface = nullptr;
	params.regedInRenderer = false;
}

Text::~Text()
{
	if (params.regedInRenderer == true)
		Renderer::get_instance()->unregister_component(this, params.renderLayer);
}