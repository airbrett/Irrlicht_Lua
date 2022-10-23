#pragma once
#include <irrlicht.h>
#include <lua.hpp>

void init_ISceneNode(lua_State* L);
void push_ISceneNode(lua_State* L, irr::scene::ISceneNode* sn);
void fill_ISceneNode(lua_State* L);
