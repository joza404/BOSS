#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <memory>

#include "../BaseComponent.h"
#include "../../BaseObject.h"
#include "../Position/Position.h"
#include "../../Resources/ImageResource.h"

class Image : public BaseComponent, public BaseObject{
public:
	//all Image parameters
	struct Parameters{
		ImageResource* resource = nullptr;

		unsigned int renderLayer;
		bool regedInRenderer;

		int x, y;
		unsigned int w, h;
	};

	//component update function
	void update();

	//set image resource
	void set_resource(ImageResource& res);
	void set_resource(const std::string& res);

	//get/set render layer
	unsigned int get_layer() const { return params.renderLayer; }
	bool set_layer(unsigned int layer);

	//returns a copy of current parameters
	Parameters get_params() const { return params; }

	//set references to other components
	void set_position(Position* pos) { positionComp = pos; }
	void set_position(const std::string& pos);
	void unset_position() { positionComp = nullptr;}

	Image(const std::string& name);
	~Image();
	Image() = delete;
	Image(const Image&) = delete;
	Image& operator=(const Image&) = delete;
private:
	Parameters params;

	//references to other components
	Position* positionComp = nullptr;
};

#endif