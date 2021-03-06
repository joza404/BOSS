cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

project(BOSS)

find_package(SDL REQUIRED)
if(NOT SDL_FOUND)
	message(SEND_ERROR "Failted to find SDL")
	return()
else()
	include_directories(${SDL_INCLUDE_DIR})
endif()

find_package(SDL_image REQUIRED)
if(NOT SDL_IMAGE_FOUND)
	message(SEND_ERROR "Failted to find SDL_image")
	return()
else()
	include_directories(${SDL_IMAGE_INCLUDE_DIRS})
endif()

find_package(SDL_ttf REQUIRED)
if(NOT SDL_TTF_FOUND)
	message(SEND_ERROR "Failted to find SDL_ttf")
	return()
else()
	include_directories(${SDL_TTF_INCLUDE_DIRS})
endif()

find_package(Lua REQUIRED)
if(NOT LUA_FOUND)
	message(SEND_ERROR "Failted to find Lua")
	return()
else()
	include_directories(${LUA_INCLUDE_DIR})
endif()

find_package(Luaponte REQUIRED)
if(NOT LUAPONTE_FOUND)
	message(SEND_ERROR "Failted to find LuaPonte")
	return()
else()
	include_directories(${LUAPONTE_INCLUDE_DIR}/../)
endif()

find_package(BOOST REQUIRED)
if(NOT Boost_FOUND)
	message(SEND_ERROR "Failted to find Boost")
	return()
else()
	include_directories(${Boost_INCLUDE_DIRS})
endif()

add_subdirectory(engine)