#pragma once
#include <irrlicht.h>
#include <lua.hpp>

void push_IrrFileSystem(lua_State* L, irr::io::IFileSystem* fs);