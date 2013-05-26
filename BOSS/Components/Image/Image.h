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

		unsigned int renderLay;

		int x, y;
		unsigned int w, h;
	};

	//component update function
	void update();

	//set image resource
	void set_resource(std::shared_ptr<ImageResource> res);
	void set_resource(std::string res);

	//get/set render lay
	unsigned int get_lay() const { return params.renderLay; }
	void set_lay(unsigned int lay) { params.renderLay = lay; }

	//returns copy of current parameters
	Parameters get_params() const { return params; }

	//set references to other components
	void set_position(const std::shared_ptr<Position> pos) { positionComp = pos; }
	void set_position(const std::string pos);
	void unset_position() { positionComp.reset(); }

	Image (const std::string name, const unsigned int id);
	~Image () {};
private:
	Parameters params;

	//references to other components
	std::weak_ptr<Position> positionComp;

	Image();
	Image(const Image&);
	Image& operator=(const Image&);
};

#endif