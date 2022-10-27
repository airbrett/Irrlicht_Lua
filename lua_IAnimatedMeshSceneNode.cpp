#include "lua_IAnimatedMeshSceneNode.h"

#include "lua_ISceneNode.h"
#include "lua_IAnimatedMesh.h"
#include "lua_util.h"

static int addShadowVolumeSceneNode(lua_State* L);
static int getMesh(lua_State* L);

void push_IAnimatedMeshSceneNode(lua_State* L, irr::scene::IAnimatedMeshSceneNode* anms)
{
	CreateObjTable(L, anms);

	fill_ISceneNode(L);

	lua_pushcfunction(L, addShadowVolumeSceneNode);
	lua_setfield(L, -2, "addShadowVolumeSceneNode");

	lua_pushcfunction(L, getMesh);
	lua_setfield(L, -2, "getMesh");
}

int addShadowVolumeSceneNode(lua_State* L)
{
	GetObjPtr<irr::scene::IAnimatedMeshSceneNode>(L)->addShadowVolumeSceneNode();
	return 0;
}

int getMesh(lua_State* L)
{
	push_IAnimatedMesh(L, GetObjPtr<irr::scene::IAnimatedMeshSceneNode>(L)->getMesh());
	return 1;
}
