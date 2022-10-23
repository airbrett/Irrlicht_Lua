#include "lua_ILightSceneNode.h"

#include "lua_util.h"

static int setAttenuation(lua_State* L);
static int setRadius(lua_State* L);

void push_ILightSceneNode(lua_State* L, irr::scene::ILightSceneNode* lsn)
{
	CreateObjTable(L, lsn);

	lua_pushcfunction(L, setAttenuation);
	lua_setfield(L, -2, "setAttenuation");

	lua_pushcfunction(L, setRadius);
	lua_setfield(L, -2, "setRadius");
}

int setAttenuation(lua_State* L)
{
	GetObjPtr<irr::scene::ILightSceneNode>(L)->getLightData().Attenuation = check_vector3df(L, 2);
	return 0;
}

int setRadius(lua_State* L)
{
	GetObjPtr<irr::scene::ILightSceneNode>(L)->getLightData().Radius = luaL_checknumber(L, 2);
	return 0;
}
