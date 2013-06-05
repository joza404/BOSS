add_executable(boss 
main.cpp

Components/Animation/Animation.cpp
Components/Image/Image.cpp
Components/Text/Text.cpp
Components/Position/Position.cpp

Renderer/Renderer.cpp

ResourceManager/AnimationResource.cpp
ResourceManager/ImageResource.cpp
ResourceManager/FontResource.cpp

Lua/Lua.cpp
)

#set_target_properties(boss PROPERTIES WIN32_EXECUTABLE TRUE) 

target_link_libraries(boss ${SDL_LIBRARY} ${SDL_IMAGE_LIBRARIES} ${SDL_TTF_LIBRARIES} ${LUA_LIBRARIES} ${LUAPONTE_LIBRARIES})