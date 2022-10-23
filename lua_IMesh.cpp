#include "lua_IMesh.h"

#include "lua_util.h"
#include "lua_IMeshBuffer.h"

static int getMeshBufferCount(lua_State* L);
static int getMeshBuffer(lua_State* L);

void push_IMesh(lua_State* L, irr::scene::IMesh* im)
{
	CreateObjTable(L, im);

	fill_IMesh(L);
}

void fill_IMesh(lua_State* L)
{
	lua_pushcfunction(L, getMeshBufferCount);
	lua_setfield(L, -2, "getMeshBufferCount");

	lua_pushcfunction(L, getMeshBuffer);
	lua_setfield(L, -2, "getMeshBuffer");
}

int getMeshBufferCount(lua_State* L)
{
	lua_pushinteger(L, GetObjPtr<irr::scene::IMesh>(L)->getMeshBufferCount());

	return 1;
}

int getMeshBuffer(lua_State* L)
{
	const irr::u32 index = static_cast<irr::u32>(luaL_checkinteger(L, 2));
	push_IMeshBuffer(L, GetObjPtr<irr::scene::IMesh>(L)->getMeshBuffer(index));

	return 1;
}
