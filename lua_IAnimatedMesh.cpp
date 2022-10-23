#include "lua_IAnimatedMesh.h"
#include "lua_IMesh.h"

#include "lua_util.h"

static int getMesh(lua_State* L);

void push_IAnimatedMesh(lua_State* L, irr::scene::IAnimatedMesh* am)
{
	CreateObjTable(L, am);

	fill_IMesh(L);

	lua_pushcfunction(L, getMesh);
	lua_setfield(L, -2, "getMesh");
}

int getMesh(lua_State* L)
{
	irr::scene::IAnimatedMesh* Mesh = GetObjPtr<irr::scene::IAnimatedMesh>(L);

	const int frame = luaL_checkinteger(L, 2);

	push_IMesh(L, Mesh->getMesh(frame));

	return 1;
}