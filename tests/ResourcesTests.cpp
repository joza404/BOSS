#include <cassert>

#include "../engine/Resources/ResourceManager.h"
#include "../engine/Resources/AnimationResource.h"
#include "../engine/Resources/ImageResource.h"
#include "../engine/Resources/FontResource.h"
#include "../engine/Resources/RigidBodyResource.h"


void test_animation_resource()
{
	ResourceManager& rm = ResourceManager::get_instance();

	AnimationResource& boy1 = rm.load_animation_res("boy1","..//game//resources//standingboy.info");
	assert(boy1.image != nullptr);
	std::cout << (bool)(boy1.image) << "\r\n";
	std::cout << (boy1.spriteNumber) << "\r\n";
	std::cout << boy1.transColor << "\r\n\r\n";

	rm.load_animation_res("boy2", "..//game//resources//standingboy2.info");
	AnimationResource& boy2 = rm.get_animation_res("boy2");
	assert(boy2.image != nullptr);
	std::cout << (bool)(boy2.image) << "\r\n";
	std::cout << (boy2.spriteNumber) << "\r\n";
	std::cout << boy2.transColor << "\r\n\r\n";

	rm.load_animation_res("boy3", "..//game//resources//standingboy2.info");
	rm.load_animation_res("boy4", "..//game//resources//standingboy2.info");
	AnimationResource& boy = rm.get_animation_res("boy1");
	assert(boy.image != nullptr);
	std::cout << (bool)(boy.image) << "\r\n";
	std::cout << (boy.spriteNumber) << "\r\n";
	std::cout << boy.transColor << "\r\n\r\n";
}

void test_image_resource()
{
	ResourceManager& rm = ResourceManager::get_instance();

	ImageResource& bg = rm.load_image_res("background", "..//game//resources//space.info");
	assert(bg.image != nullptr);
	ImageResource& bg2 = rm.get_image_res("background");
}

void test_font_resource()
{
	ResourceManager& rm = ResourceManager::get_instance();

	FontResource& font1 = rm.load_font_res("font1", "..//game//resources//font1.info");
	assert(font1.font != nullptr);
	assert(font1.size == 20);
}

void test_rigidbody_resource()
{
	ResourceManager& rm = ResourceManager::get_instance();
	RigidBodyResource& res = rm.load_rigidbody_res("rigidbody1", "..//game//resources//rigidbody1.info");
	assert(res.frameNumber == 4);
	assert(res.frameList.size() == 4);

	for(auto& frame : res.frameList){
		std::cout << "New frame: \r\n";
		for(auto& square : frame){
			std::cout << "Name: " << square.name << "\r\n";
			std::cout << "x1=" << square.x1 << "  y1=" << square.y1 << "\r\n";
			std::cout << "x2=" << square.x2 << "  y2=" << square.y2 << "\r\n";
		}
	}
}