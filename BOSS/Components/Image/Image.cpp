#include "Image.h"
#include "../ComponentManager.h"
#include "../../ResourceManager/ResourceManager.h"
#include "../../Renderer/Renderer.h"

//local macroses (in .cpp)
#define DEFAULT_RENDER_LAYER 0
#define DEFAULT_X 0
#define DEFAULT_Y 0

void Image::update()
{
	//if position component exists
	if (positionComp.expired() == false){
		auto shared = positionComp.lock();
		params.x = shared->get_x();
		params.y = shared->get_y();
	}
}

void Image::set_resource(const std::shared_ptr<ImageResource>& res)
{
	params.resource = res;
	params.w = res->image->w;
	params.h = res->image->h;
}


void Image::set_resource(const std::string& res)
{
	params.resource = ResourceManager::get_instance()->get_resource<ImageResource>(res);
	params.w = params.resource->image->w;
	params.h = params.resource->image->h;
}

bool Image::set_layer(unsigned int layer)
{
	Renderer* renderer = Renderer::get_instance();
	if (renderer->last_layer() > layer)
		return false;

	renderer->unregister_component(this, params.renderLayer);
	params.renderLayer = layer;
	renderer->register_component(this, layer);
	return true;
}

void Image::set_position(const std::string& pos)
{
	positionComp = ComponentManager::get_instance()->get_component<Position>(pos);
}

Image::Image(const std::string& _name, const unsigned int _id) : BaseObject(_name, _id)
{
	params.renderLayer = DEFAULT_RENDER_LAYER;
	params.x = DEFAULT_X;
	params.y = DEFAULT_Y;
	params.x = params.y = 0;

	Renderer::get_instance()->register_component(this, params.renderLayer);
}

Image::~Image()
{
	Renderer::get_instance()->unregister_component(this, params.renderLayer);
}