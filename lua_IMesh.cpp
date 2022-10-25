#include "lua_IMesh.h"

#include "lua_util.h"
#include "lua_IMeshBuffer.h"

static int getMeshBufferCount(lua_State* L);
static int getMeshBuffer(lua_State* L);
static int getBoundingBox(lua_State* L);

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

	lua_pushcfunction(L, getBoundingBox);
	lua_setfield(L, -2, "getBoundingBox");
}

int getMeshBufferCount(lua_State* L)
{
	lua_pushinteger(L, GetObjPtr<irr::scene::IMesh>(L)->getMeshBufferCount());

	return 1;
}

int getMeshBuffer(lua_State* L)
{
	const irr::u32 index = check_u32(L, 2);
	push_IMeshBuffer(L, GetObjPtr<irr::scene::IMesh>(L)->getMeshBuffer(index));

	return 1;
}

int getBoundingBox(lua_State* L)
{
	push_aabbox3df(L, GetObjPtr<irr::scene::IMesh>(L)->getBoundingBox());
	return 1;
}
