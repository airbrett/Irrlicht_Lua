#include "lua_ISceneNodeAnimator.h"

#include "lua_util.h"

void push_ISceneNodeAnimator(lua_State* L, irr::scene::ISceneNodeAnimator* sn)
{
	CreateObjTable(L, sn);

	
}
