#include "../Input/Input.h"
bool bind_register_key(std::string key, std::string path);
bool bind_key_pressed(std::string key);
void bind_class_input();

#include "../NEW/ResourceManager/ResourceManager.h"
bool bind_load_animation_resource(std::string path, std::wstring name);
bool bind_load_image_resource(std::string path, std::wstring name);
void bind_class_resmngr();
