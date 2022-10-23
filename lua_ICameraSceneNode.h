#pragma once

#include <irrlicht.h>
#include <lua.hpp>

void init_ICameraSceneNode(lua_State* L);
void push_ICameraSceneNode(lua_State* L, irr::scene::ICameraSceneNode* csn);
