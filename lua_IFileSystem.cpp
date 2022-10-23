#include "lua_IFileSystem.h"

#include "lua_util.h"

static int addFileArchive(lua_State* L);

void push_IrrFileSystem(lua_State* L, irr::io::IFileSystem* fs)
{
	CreateObjTable(L, fs);

	lua_pushcfunction(L, addFileArchive);
	lua_setfield(L, -2, "addFileArchive");
}

int addFileArchive(lua_State* L)
{
	const bool Success = GetObjPtr<irr::io::IFileSystem>(L)->addFileArchive(
		luaL_checkstring(L, 2)
	);

	lua_pushboolean(L, Success);

	return 1;
}
