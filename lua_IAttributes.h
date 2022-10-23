#pragma once
#include <irrlicht.h>
#include <lua.hpp>

void init_IAttributes(lua_State* L);
void push_IAttributes(lua_State* L, irr::io::IAttributes* att);
