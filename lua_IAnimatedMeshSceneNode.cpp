#include "lua_IAnimatedMeshSceneNode.h"

#include "lua_ISceneNode.h"
#include "lua_util.h"

static int addShadowVolumeSceneNode(lua_State* L);

void push_IAnimatedMeshSceneNode(lua_State* L, irr::scene::IAnimatedMeshSceneNode* anms)
{
	CreateObjTable(L, anms);

	fill_ISceneNode(L);

	lua_pushcfunction(L, addShadowVolumeSceneNode);
	lua_setfield(L, -2, "addShadowVolumeSceneNode");
}

int addShadowVolumeSceneNode(lua_State* L)
{
	GetObjPtr<irr::scene::IAnimatedMeshSceneNode>(L)->addShadowVolumeSceneNode();
	return 0;
}
