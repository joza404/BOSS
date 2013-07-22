#include "Image.h"
#include "../ComponentManager.h"
#include "../../Resources/ResourceManager.h"
#include "../../Renderer/Renderer.h"

//local macroses (in .cpp)
#define DEFAULT_RENDER_LAYER 0
#define DEFAULT_X 0
#define DEFAULT_Y 0

//component update function
void Image::update()
{
	//if position component exists
	if (positionComp != nullptr){
		params.x = positionComp->get_x();
		params.y = positionComp->get_y();
	}
}

void Image::set_resource(ImageResource& res)
{
	params.resource = &res;
	params.w = res.image->w;
	params.h = res.image->h;

	//first time here
	if (params.regedInRenderer == false){
		Renderer::get_instance().register_component(this, params.renderLayer);
		params.regedInRenderer = true;
	}
}


void Image::set_resource(const std::string& res)
{
	params.resource = &ResourceManager::get_instance().get_image_res(res);
	params.w = params.resource->image->w;
	params.h = params.resource->image->h;

	//first time here
	if (params.regedInRenderer == false){
		Renderer::get_instance().register_component(this, params.renderLayer);
		params.regedInRenderer = true;
	}
}

bool Image::set_layer(unsigned int layer)
{
	Renderer& renderer = Renderer::get_instance();
	if (renderer.last_layer() > layer)
		return false;

	params.renderLayer = layer;
	if (params.regedInRenderer == false){
		renderer.unregister_component(this, params.renderLayer);
		renderer.register_component(this, layer);
	}
	return true;
}

void Image::set_position(const std::string& pos)
{
	positionComp = ComponentManager::get_instance().get_position_comp(pos);
}

Image::Image(const std::string& _name) : BaseObject(_name)
{
	params.renderLayer = DEFAULT_RENDER_LAYER;
	params.x = DEFAULT_X;
	params.y = DEFAULT_Y;
	params.regedInRenderer = false;
	params.resource = nullptr;
	positionComp = nullptr;
}

Image::~Image()
{
	if (params.regedInRenderer == true)
		Renderer::get_instance().unregister_component(this, params.renderLayer);
}