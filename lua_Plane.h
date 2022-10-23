#pragma once

#include <irrlicht.h>
#include <lua.hpp>

void init_Plane(lua_State* L);
void push_Plane(lua_State* L, irr::core::plane3df* p);
