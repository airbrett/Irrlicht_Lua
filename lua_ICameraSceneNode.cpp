#include "lua_ICameraSceneNode.h"

#include "lua_ISceneNode.h"
#include "lua_util.h"
#include "SceneNodeAnimator.h"

const static char* MetaTableName = "__ICameraSceneNode_meta";

static int bindTargetAndRotation(lua_State* L);
static int setRotation(lua_State* L);
static int setRotation(lua_State* L);
static int setNearValue(lua_State* L);
static int getNearValue(lua_State* L);

void init_ICameraSceneNode(lua_State* L)
{
	lua_createtable(L, 0, 20);

	fill_ISceneNode(L);

	lua_pushcfunction(L, bindTargetAndRotation);
	lua_setfield(L, -2, "bindTargetAndRotation");

	lua_pushcfunction(L, setRotation);
	lua_setfield(L, -2, "setRotation");

	lua_pushcfunction(L, setNearValue);
	lua_setfield(L, -2, "setNearValue");

	lua_pushcfunction(L, getNearValue);
	lua_setfield(L, -2, "getNearValue");

	luaL_newmetatable(L, MetaTableName);
	lua_pushvalue(L, -2);
	lua_setfield(L, -2, "__index");
	lua_pop(L, 2);
}

void push_ICameraSceneNode(lua_State* L, irr::scene::ICameraSceneNode* csn)
{
	CreateObjTable(L, csn);

	luaL_setmetatable(L, MetaTableName);
}

int bindTargetAndRotation(lua_State* L)
{
	GetObjPtr<irr::scene::ICameraSceneNode>(L)->bindTargetAndRotation(check_boolean(L, 2));
	return 0;
}

int setRotation(lua_State* L)
{
	GetObjPtr<irr::scene::ICameraSceneNode>(L)->setRotation(check_vector3df(L, 2));
	return 0;
}

int setNearValue(lua_State* L)
{
	GetObjPtr<irr::scene::ICameraSceneNode>(L)->setNearValue(static_cast<irr::f32>(luaL_checknumber(L, 2)));
	return 0;
}

int getNearValue(lua_State* L)
{
	lua_pushnumber(L, GetObjPtr<irr::scene::ICameraSceneNode>(L)->getNearValue());
	return 1;
}
