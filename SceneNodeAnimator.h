#pragma once

#include <irrlicht.h>
#include <lua.hpp>

class SceneNodeAnimator : public irr::scene::ISceneNodeAnimator
{
private:
	lua_State* mL;
	const int mRef;
	irr::u32 mLastTime;

public:
	SceneNodeAnimator(lua_State* L, const int ref);
	void animateNode(irr::scene::ISceneNode* node, irr::u32 timeMs);
	irr::scene::ISceneNodeAnimator* createClone(irr::scene::ISceneNode* node, irr::scene::ISceneManager* newManager = 0);
};