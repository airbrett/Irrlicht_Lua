#include "lua_matrix4.h"

#include <irrlicht.h>
#include "lua_util.h"

const static char* MetaTableName = "__mat4_meta";

static int new_matrix4(lua_State* L);
static int delete_matrix4(lua_State* L);
static int transformVect(lua_State* L);
static int mul(lua_State* L);
static int gc(lua_State* L);
static int getTranslation(lua_State* L);
static int setTranslation(lua_State* L);
static int setRotationDegrees(lua_State* L);
static int getRotationDegrees(lua_State* L);
static int setRotationRadians(lua_State* L);

void init_matrix4(lua_State* L)
{
	lua_createtable(L, 0, 10);

	lua_pushcfunction(L, new_matrix4);
	lua_setfield(L, -2, "new");

	lua_pushcfunction(L, delete_matrix4);
	lua_setfield(L, -2, "delete");

	lua_pushcfunction(L, transformVect);
	lua_setfield(L, -2, "transformVect");

	lua_pushcfunction(L, getTranslation);
	lua_setfield(L, -2, "getTranslation");

	lua_pushcfunction(L, setTranslation);
	lua_setfield(L, -2, "setTranslation");

	lua_pushcfunction(L, getRotationDegrees);
	lua_setfield(L, -2, "getRotationDegrees");

	lua_pushcfunction(L, setRotationDegrees);
	lua_setfield(L, -2, "setRotationDegrees");

	lua_pushcfunction(L, setRotationRadians);
	lua_setfield(L, -2, "setRotationRadians");

	luaL_newmetatable(L, MetaTableName);
	lua_pushvalue(L, -2);
	lua_setfield(L, -2, "__index");

	lua_pushcfunction(L, mul);
	lua_setfield(L, -2, "__mul");
	//lua_pop(L, 1);

	lua_pushcfunction(L, gc);
	lua_setfield(L, -2, "__gc");
	lua_pop(L, 1);

	lua_setfield(L, -2, "matrix4");
}

void push_matrix4(lua_State* L, const irr::core::matrix4* mat4)
{
	CreateObjTable(L, mat4);

	luaL_setmetatable(L, MetaTableName);
}

int new_matrix4(lua_State* L)
{
	push_matrix4(L, new irr::core::matrix4());
	return 1;
}

int delete_matrix4(lua_State* L)
{
	lua_getfield(L, -1, "deleted");
	bool deleted = lua_toboolean(L, -1);

	if (!deleted)
	{
		delete GetObjPtr<irr::core::matrix4>(L);

		lua_pushboolean(L, true);
		lua_setfield(L, -2, "deleted");
	}

	return 0;
}

int mul(lua_State* L)
{
	//incomplete
	irr::core::matrix4* mat = GetObjPtr<irr::core::matrix4>(L);

	*mat *= check_f32(L, 2);

	lua_pushvalue(L, 1);
	return 1;
}

int gc(lua_State* L)
{
	lua_getfield(L, -1, "deleted");
	bool deleted = lua_toboolean(L, -1);

	if (!deleted)
	{
		delete GetObjPtr<irr::core::matrix4>(L);

		lua_pushboolean(L, true);
		lua_setfield(L, -2, "deleted");
	}

	return 0;
}

int transformVect(lua_State* L)
{
	irr::core::matrix4* mat = GetObjPtr<irr::core::matrix4>(L);
	irr::core::vector3df vec = check_vector3df(L, 2);
	mat->transformVect(vec);
	push_vector3df(L, vec);
	return 1;
}

int getTranslation(lua_State* L)
{
	push_vector3df(L, GetObjPtr<irr::core::matrix4>(L)->getTranslation());
	return 1;
}

int setTranslation(lua_State* L)
{
	GetObjPtr<irr::core::matrix4>(L)->setTranslation(check_vector3df(L, 2));
	return 0;
}

int getRotationDegrees(lua_State* L)
{
	push_vector3df(L, GetObjPtr<irr::core::matrix4>(L)->getRotationDegrees());
	return 0;
}

int setRotationDegrees(lua_State* L)
{
	GetObjPtr<irr::core::matrix4>(L)->setRotationDegrees(check_vector3df(L, 2));
	return 0;
}

int setRotationRadians(lua_State* L)
{
	GetObjPtr<irr::core::matrix4>(L)->setRotationRadians(check_vector3df(L, 2));
	return 0;
}
