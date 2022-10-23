#pragma once
#include <irrlicht.h>
#include <lua.hpp>

void push_IVideoDriver(lua_State* L, irr::video::IVideoDriver* driver);