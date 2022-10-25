#pragma once
#include <irrlicht.h>
#include <lua.hpp>

void init_matrix4(lua_State* L);
void push_matrix4(lua_State* L, const irr::core::matrix4* mat4);