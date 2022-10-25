#include "lua_ISceneManager.h"

#include "lua_util.h"
#include "lua_IAnimatedMesh.h"
#include "lua_ISceneNode.h"
#include "lua_IAnimatedMeshSceneNode.h"
#include "lua_ICameraSceneNode.h"
#include "lua_ILightSceneNode.h"
#include "lua_IAttributes.h"

static int getMesh(lua_State* L);
static int addOctreeSceneNode(lua_State* L);
static int addCameraSceneNodeFPS(lua_State* L);
static int addCameraSceneNode(lua_State* L);
static int drawAll(lua_State* L);
static int addAnimatedMeshSceneNode(lua_State* L);
static int addLightSceneNode(lua_State* L);
static int addSceneNode(lua_State* L);
static int getSceneNodeFromName(lua_State* L);
static int addExternalMeshLoader(lua_State* L);

void push_ISceneManager(lua_State* L, irr::scene::ISceneManager* smgr)
{
	CreateObjTable(L, smgr);

	lua_pushcfunction(L, getMesh);
	lua_setfield(L, -2, "getMesh");

	lua_pushcfunction(L, addOctreeSceneNode);
	lua_setfield(L, -2, "addOctreeSceneNode");

	lua_pushcfunction(L, addCameraSceneNodeFPS);
	lua_setfield(L, -2, "addCameraSceneNodeFPS");

	lua_pushcfunction(L, addCameraSceneNode);
	lua_setfield(L, -2, "addCameraSceneNode");

	lua_pushcfunction(L, addAnimatedMeshSceneNode);
	lua_setfield(L, -2, "addAnimatedMeshSceneNode");

	lua_pushcfunction(L, addLightSceneNode);
	lua_setfield(L, -2, "addLightSceneNode");

	lua_pushcfunction(L, addSceneNode);
	lua_setfield(L, -2, "addSceneNode");

	lua_pushcfunction(L, drawAll);
	lua_setfield(L, -2, "drawAll");

	push_IAttributes(L, smgr->getParameters());
	lua_setfield(L, -2, "parameters");

	lua_pushcfunction(L, getSceneNodeFromName);
	lua_setfield(L, -2, "getSceneNodeFromName");

	lua_pushcfunction(L, addExternalMeshLoader);
	lua_setfield(L, -2, "addExternalMeshLoader");
}

int getMesh(lua_State* L)
{
	const char* alternativeCacheName;

	if (lua_gettop(L) > 2)
		alternativeCacheName = luaL_checkstring(L, 3);
	else
		alternativeCacheName = nullptr;

	irr::scene::IAnimatedMesh* Mesh = GetObjPtr<irr::scene::ISceneManager>(L)->getMesh(
		luaL_checkstring(L, 2),
		alternativeCacheName
	);

	push_IAnimatedMesh(L, Mesh);

	return 1;
}

int addOctreeSceneNode(lua_State* L)
{
	irr::scene::ISceneManager* Scmr = GetObjPtr<irr::scene::ISceneManager>(L);
	irr::scene::IMesh* Mesh = GetObjPtr<irr::scene::IMesh>(L, 2);

	irr::scene::ISceneNode* Node = Scmr->addOctreeSceneNode(Mesh);

	push_ISceneNode(L, Node);

	return 1;
}

int addCameraSceneNodeFPS(lua_State* L)
{
	push_ICameraSceneNode(L, GetObjPtr<irr::scene::ISceneManager>(L)->addCameraSceneNodeFPS());

	return 1;
}

int addCameraSceneNode(lua_State* L)
{
	push_ICameraSceneNode(L, GetObjPtr<irr::scene::ISceneManager>(L)->addCameraSceneNode());

	return 1;
}

int addAnimatedMeshSceneNode(lua_State* L)
{
	irr::scene::IAnimatedMeshSceneNode* anms = GetObjPtr<irr::scene::ISceneManager>(L)->addAnimatedMeshSceneNode(GetObjPtr<irr::scene::IAnimatedMesh>(L, 2));

	push_IAnimatedMeshSceneNode(L, anms);

	return 1;
}

int addLightSceneNode(lua_State* L)
{
	irr::scene::ISceneNode* parent = nullptr;
	irr::core::vector3df position(0, 0, 0);
	irr::video::SColorf color(1.0f, 1.0f, 1.0f);
	irr::f32 radius = 100.0f;
	irr::s32 id = -1;

	if (lua_gettop(L) > 1 && !lua_isnil(L, 2))
		parent = GetObjPtr<irr::scene::ISceneNode>(L, 2);

	if (lua_gettop(L) > 2 && !lua_isnil(L, 3))
		position = check_vector3df(L, 3);

	if (lua_gettop(L) > 3 && !lua_isnil(L, 4))
		color = check_scolorf(L, 4);

	if (lua_gettop(L) > 4 && !lua_isnil(L, 5))
		radius = static_cast<irr::f32>(luaL_checknumber(L, 5));

	if (lua_gettop(L) > 5 && !lua_isnil(L, 6))
		id = static_cast<irr::s32>(luaL_checkinteger(L, 6));

	push_ILightSceneNode(L, GetObjPtr<irr::scene::ISceneManager>(L)->addLightSceneNode(parent, position, color, radius, id));

	return 1;
}

int addSceneNode(lua_State* L)
{
	irr::scene::ISceneNode* parent;

	if (lua_gettop(L) > 2)
		parent = GetObjPtr<irr::scene::ISceneNode>(L, 3);
	else
		parent = nullptr;

	irr::scene::ISceneNode* Node = GetObjPtr<irr::scene::ISceneManager>(L)->addSceneNode(luaL_checkstring(L, 2), parent);

	push_ISceneNode(L, Node);

	return 1;
}


int drawAll(lua_State* L)
{
	GetObjPtr<irr::scene::ISceneManager>(L)->drawAll();
	return 0;
}

int getSceneNodeFromName(lua_State* L)
{
	irr::scene::ISceneNode* start;

	if (lua_gettop(L) > 2)
		start = GetObjPtr<irr::scene::ISceneNode>(L, 3);
	else
		start = nullptr;

	irr::scene::ISceneNode* result = GetObjPtr<irr::scene::ISceneManager>(L)->getSceneNodeFromName(luaL_checkstring(L, 2), start);
	
	if (result != nullptr)
		switch (result->getType())
		{
		case irr::scene::ESNT_ANIMATED_MESH:
			push_IAnimatedMeshSceneNode(L, dynamic_cast<irr::scene::IAnimatedMeshSceneNode*>(result));
			break;
		default:
			push_ISceneNode(L, result);
		}
	else
		lua_pushnil(L);

	return 1;
}

int addExternalMeshLoader(lua_State* L)
{
	GetObjPtr<irr::scene::ISceneManager>(L)->addExternalMeshLoader(GetObjPtr<irr::scene::IMeshLoader>(L, 2));
	return 0;
}
