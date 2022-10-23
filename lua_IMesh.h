#pragma once
#include <irrlicht.h>
#include <lua.hpp>

void push_IMesh(lua_State* L, irr::scene::IMesh* im);
void fill_IMesh(lua_State* L);