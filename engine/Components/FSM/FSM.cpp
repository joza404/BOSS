#include "FSM.h"

//component update function
void FSM::update()
{
	if (currentState.is_valid()){
		currentState["Execute"](&go);
	}
}

//change to a new state
void FSM::change_state(const luaponte::object& newState)
{
 	//call the Exit method of the existing state
	currentState["Exit"](&go);

 	//change state to the new state
	currentState = newState;

	//call the Entry method of the new state
	currentState["Enter"](&go);
}

FSM::FSM(const std::string& name, GameObject& _go) : go(_go), BaseObject(name)
{

}