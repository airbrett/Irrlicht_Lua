#pragma once

#include <irrlicht.h>
#include <lua.hpp>

void init_IrrlichtDevice(lua_State* L);
void push_IrrlichtDevice(lua_State* L, irr::IrrlichtDevice* device);