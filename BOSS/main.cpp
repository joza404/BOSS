#include <locale>
#include <SDL_ttf.h>
#include <memory>

#include "ResourceManager\AnimationResource.h"
#include "ResourceManager\FontResource.h"
#include "ResourceManager\ImageResource.h"
#include "ResourceManager\ResourceManager.h"


int main(int argc,char** argv)
{
	setlocale(LC_ALL, "russian_russia.1251");
	TTF_Init();

	ResourceManager* rm = ResourceManager::get_instance();
	rm->load_resource<FontResource>("..//game//fonts//font1.info", "bullet");
	rm->load_resource<FontResource>("..//game//fonts//font2.info", "bullet");
	auto x = rm->get_resource<FontResource>("bulletf");

	return 0;
}