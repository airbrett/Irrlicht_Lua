#pragma once
#include <irrlicht.h>
#include <lua.hpp>

void init_IMeshBuffer(lua_State* L);
void push_IMeshBuffer(lua_State* L, irr::scene::IMeshBuffer* imb);