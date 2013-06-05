#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <memory>

#include "../BaseComponent.h"
#include "../../BaseObject.h"
#include "../Position/Position.h"
#include "../../ResourceManager/ImageResource.h"

class Image : public BaseComponent, public BaseObject{
public:
	//all Image parameters
	struct Parameters{
		std::shared_ptr<ImageResource> resource;

		unsigned int renderLayer;
		bool regedInRenderer;

		int x, y;
		unsigned int w, h;
	};

	//component update function
	void update();

	//set image resource
	void set_resource(const std::shared_ptr<ImageResource>& res);
	void set_resource(const std::string& res);

	//get/set render layer
	unsigned int get_layer() const { return params.renderLayer; }
	bool set_layer(unsigned int layer);

	//returns a copy of current parameters
	Parameters get_params() const { return params; }

	//set references to other components
	void set_position(const std::shared_ptr<Position>& pos) { positionComp = pos; }
	void set_position(const std::string& pos);
	void unset_position() { positionComp.reset(); }

	Image(const std::string& name, const unsigned int id);
	~Image();
	Image() = delete;
	Image(const Image&) = delete;
	Image& operator=(const Image&) = delete;
private:
	Parameters params;

	//references to other components
	std::weak_ptr<Position> positionComp;
};

#endif