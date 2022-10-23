#include "SceneNodeAnimator.h"

#include "lua_ISceneNode.h"

#include <limits>

SceneNodeAnimator::SceneNodeAnimator(lua_State* L, const int ref) :
	mL(L),
	mRef(ref),
	mLastTime(std::numeric_limits<irr::s32>::min())
{
}

void SceneNodeAnimator::animateNode(irr::scene::ISceneNode* node, irr::u32 timeMs)
{
	if (mLastTime == std::numeric_limits<irr::s32>::min())
		mLastTime = timeMs;

	const lua_Number dt = (static_cast<lua_Number>(timeMs) - mLastTime) / 1000.0;
	mLastTime = timeMs;

	lua_rawgeti(mL, LUA_REGISTRYINDEX, mRef);
	const int Table = lua_gettop(mL);

	lua_getfield(mL, -1, "animateNode");

	lua_pushvalue(mL, Table);
	//store both the node and the callback instead. Otherwise this cast is a problem..
	push_ISceneNode(mL, node);
	//lua_pushinteger(mL, timeMs);
	lua_pushnumber(mL, dt);//dt seems more useful than timeMs

	lua_call(mL, 3, 0);
}

irr::scene::ISceneNodeAnimator* SceneNodeAnimator::createClone(irr::scene::ISceneNode* node, irr::scene::ISceneManager* newManager)
{
	//what to do with node and newManager?
	return new SceneNodeAnimator(mL, mRef);
}
