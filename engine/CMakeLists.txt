add_executable(boss 
main.cpp

Input/Input.cpp

Components/Animation/Animation.cpp
Components/Image/Image.cpp
Components/Text/Text.cpp
Components/Position/Position.cpp
Components/Movement/Movement.cpp
Components/FSM/FSM.cpp
Components/Script/Script.cpp
Components/ComponentManager.cpp

Renderer/Renderer.cpp

Resources/AnimationResource.cpp
Resources/ImageResource.cpp
Resources/FontResource.cpp
Resources/RigidBodyResource.cpp
Resources/ResourceManager.cpp

GameObject/GameObject.cpp
GameObject/GameObjectManager.cpp

Lua/Lua.cpp
)

#set_target_properties(boss PROPERTIES WIN32_EXECUTABLE TRUE) 

target_link_libraries(boss ${SDL_LIBRARY} ${SDL_IMAGE_LIBRARIES} ${SDL_TTF_LIBRARIES} ${LUA_LIBRARIES} ${LUAPONTE_LIBRARIES})