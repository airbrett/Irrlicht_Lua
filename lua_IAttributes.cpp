#include "lua_IAttributes.h"

#include "lua_util.h"

const static char* MetaTableName = "__Attribute_meta";

static int setAttribute(lua_State* L);

void init_IAttributes(lua_State* L)
{
	lua_createtable(L, 0, 4);

	lua_pushcfunction(L, setAttribute);
	lua_setfield(L, -2, "setAttribute");


	luaL_newmetatable(L, MetaTableName);
	lua_pushvalue(L, -2);
	lua_setfield(L, -2, "__index");
	lua_pop(L, 2);
}

void push_IAttributes(lua_State* L, irr::io::IAttributes* att)
{
	CreateObjTable(L, att);

	luaL_setmetatable(L, MetaTableName);
}

int setAttribute(lua_State* L)
{
	GetObjPtr<irr::io::IAttributes>(L)->setAttribute(luaL_checkstring(L, 2), check_boolean(L, 3));
	return 0;
}
