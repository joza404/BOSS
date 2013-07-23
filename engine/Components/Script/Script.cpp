#include "Script.h"

//component update function
void Script::update()
{
	if (script.is_valid()){
		script["Execute"](&go);
	}
}

Script::Script(const std::string& name, GameObject& _go, const luaponte::object& _script)
: BaseObject(name), go(_go), script(_script)
{

}