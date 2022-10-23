#include "lua_Plane.h"

#include "lua_util.h"

const static char* MetaTableName = "__Plane_meta";

int new_Plane(lua_State* L);
int getDistanceTo(lua_State* L);
int getIntersectionWithLine(lua_State* L);
int getIntersectionWithLimitedLine(lua_State* L);

void init_Plane(lua_State* L)
{
	lua_createtable(L, 0, 4);

	lua_pushcfunction(L, new_Plane);
	lua_setfield(L, -2, "new");
	lua_pushcfunction(L, getDistanceTo);
	lua_setfield(L, -2, "getDistanceTo");
	lua_pushcfunction(L, getIntersectionWithLine);
	lua_setfield(L, -2, "getIntersectionWithLine");
	lua_pushcfunction(L, getIntersectionWithLimitedLine);
	lua_setfield(L, -2, "getIntersectionWithLimitedLine");


	luaL_newmetatable(L, MetaTableName);
	lua_pushvalue(L, -2);
	lua_setfield(L, -2, "__index");
	lua_pop(L, 1);

	lua_setfield(L, -2, "plane");
}

void push_Plane(lua_State* L, irr::core::plane3df* p)
{
	CreateObjTable(L, p);

	luaL_setmetatable(L, MetaTableName);
}

int new_Plane(lua_State* L)
{
	push_Plane(L, new irr::core::plane3df(check_vector3df(L, 1), check_vector3df(L, 1)));
	return 1;
}

int getDistanceTo(lua_State* L)
{
	lua_pushnumber(L, GetObjPtr<irr::core::plane3df>(L)->getDistanceTo(check_vector3df(L, 2)));
	return 1;
}

int getIntersectionWithLine(lua_State* L)
{
	irr::core::vector3df out;
	const bool intersection = GetObjPtr<irr::core::plane3df>(L)->getIntersectionWithLine(check_vector3df(L, 2), check_vector3df(L, 3), out);
	lua_pushboolean(L, intersection);
	
	if (intersection)
	{
		push_vector3df(L, out);
		return 2;
	}

	return 1;
}

int getIntersectionWithLimitedLine(lua_State* L)
{
	irr::core::vector3df out;
	const bool intersection = GetObjPtr<irr::core::plane3df>(L)->getIntersectionWithLimitedLine(check_vector3df(L, 2), check_vector3df(L, 3), out);
	lua_pushboolean(L, intersection);

	if (intersection)
	{
		push_vector3df(L, out);
		return 2;
	}

	return 1;
}
