#include "lua_ISceneNode.h"

#include "SceneNodeAnimator.h"
#include "lua_util.h"
#include "lua_matrix4.h"

const static char* MetaTableName = "__ISceneNode_meta";

static int setPosition(lua_State* L);
static int getPosition(lua_State* L);
static int setRotation(lua_State* L);
static int getRotation(lua_State* L);
static int setMaterialFlag(lua_State* L);
static int setMaterialType(lua_State* L);
static int addAnimator(lua_State* L);
static int updateAbsolutePosition(lua_State* L);
static int addChild(lua_State* L);
static int setDebugDataVisible(lua_State* L);
static int setMaterialGouraudShading(lua_State* L);
static int remove(lua_State* L);
static int getChild(lua_State* L);
static int getNumChildren(lua_State* L);
static int getName(lua_State* L);
static int getBoundingBox(lua_State* L);
static int getAbsoluteTransformation(lua_State* L);

void init_ISceneNode(lua_State* L)
{
	lua_createtable(L, 0, 20);

	fill_ISceneNode(L);

	luaL_newmetatable(L, MetaTableName);
	lua_pushvalue(L, -2);
	lua_setfield(L, -2, "__index");
	lua_pop(L, 2);
}

void push_ISceneNode(lua_State* L, irr::scene::ISceneNode* sn)
{
	CreateObjTable(L, sn);

	luaL_setmetatable(L, MetaTableName);
}

void fill_ISceneNode(lua_State* L)
{
	lua_pushcfunction(L, setPosition);
	lua_setfield(L, -2, "setPosition");

	lua_pushcfunction(L, getPosition);
	lua_setfield(L, -2, "getPosition");

	lua_pushcfunction(L, setRotation);
	lua_setfield(L, -2, "setRotation");

	lua_pushcfunction(L, getRotation);
	lua_setfield(L, -2, "getRotation");

	lua_pushcfunction(L, setMaterialFlag);
	lua_setfield(L, -2, "setMaterialFlag");

	lua_pushcfunction(L, setMaterialType);
	lua_setfield(L, -2, "setMaterialType");

	lua_pushcfunction(L, addAnimator);
	lua_setfield(L, -2, "addAnimator");

	lua_pushcfunction(L, updateAbsolutePosition);
	lua_setfield(L, -2, "updateAbsolutePosition");

	lua_pushcfunction(L, addChild);
	lua_setfield(L, -2, "addChild");

	lua_pushcfunction(L, setDebugDataVisible);
	lua_setfield(L, -2, "setDebugDataVisible");

	lua_pushcfunction(L, setMaterialGouraudShading);
	lua_setfield(L, -2, "setMaterialGouraudShading");

	lua_pushcfunction(L, remove);
	lua_setfield(L, -2, "remove");

	lua_pushcfunction(L, getChild);
	lua_setfield(L, -2, "getChild");

	lua_pushcfunction(L, getNumChildren);
	lua_setfield(L, -2, "getNumChildren");

	lua_pushcfunction(L, getName);
	lua_setfield(L, -2, "getName");

	lua_pushcfunction(L, getBoundingBox);
	lua_setfield(L, -2, "getBoundingBox");

	lua_pushcfunction(L, getAbsoluteTransformation);
	lua_setfield(L, -2, "getAbsoluteTransformation");
}

int setPosition(lua_State* L)
{
	GetObjPtr<irr::scene::ISceneNode>(L)->setPosition(check_vector3df(L, 2));
	return 0;
}

int getPosition(lua_State* L)
{
	push_vector3df(L, GetObjPtr<irr::scene::ISceneNode>(L)->getPosition());
	return 1;
}

int setRotation(lua_State* L)
{
	GetObjPtr<irr::scene::ISceneNode>(L)->setRotation(check_vector3df(L, 2));
	return 0;
}

int getRotation(lua_State* L)
{
	push_vector3df(L, GetObjPtr<irr::scene::ISceneNode>(L)->getRotation());
	return 1;
}

int setMaterialFlag(lua_State* L)
{
	GetObjPtr<irr::scene::ISceneNode>(L)->setMaterialFlag(static_cast<irr::video::E_MATERIAL_FLAG>(luaL_checkinteger(L, 2)), check_boolean(L, 3));
	return 0;
}

int setMaterialType(lua_State* L)
{
	GetObjPtr<irr::scene::ISceneNode>(L)->setMaterialType(static_cast<irr::video::E_MATERIAL_TYPE>(luaL_checkinteger(L, 2)));
	return 0;
}

int addAnimator(lua_State* L)
{
	const int ref = luaL_ref(L, LUA_REGISTRYINDEX);
	irr::scene::ISceneNodeAnimator* anm = new SceneNodeAnimator(L, ref);
	GetObjPtr<irr::scene::ISceneNode>(L)->addAnimator(anm);
	anm->drop();

	return 0;
}

int updateAbsolutePosition(lua_State* L)
{
	GetObjPtr<irr::scene::ISceneNode>(L)->updateAbsolutePosition();
	return 0;
}

int addChild(lua_State* L)
{
	GetObjPtr<irr::scene::ISceneNode>(L)->addChild(GetObjPtr<irr::scene::ISceneNode>(L, 2));
	return 0;
}

int setDebugDataVisible(lua_State* L)
{
	GetObjPtr<irr::scene::ISceneNode>(L)->setDebugDataVisible(static_cast<irr::u32>(luaL_checkinteger(L, 2)));
	return 0;
}

int setMaterialGouraudShading(lua_State* L)
{
	const irr::u32 MatNum = static_cast<irr::u32>(luaL_checkinteger(L, 2));

	GetObjPtr<irr::scene::ISceneNode>(L)->getMaterial(MatNum).GouraudShading = check_boolean(L, 3);
	return 0;
}

int remove(lua_State* L)
{
	GetObjPtr<irr::scene::ISceneNode>(L)->remove();
	return 0;
}

int getChild(lua_State* L)
{
	const irr::core::list<irr::scene::ISceneNode*> Children = GetObjPtr<irr::scene::ISceneNode>(L)->getChildren();
	push_ISceneNode(L, *(Children.begin() + check_s32(L, 2)));
	return 1;
}

int getNumChildren(lua_State* L)
{
	lua_pushinteger(L, GetObjPtr<irr::scene::ISceneNode>(L)->getChildren().size());
	return 1;
}

int getName(lua_State* L)
{
	lua_pushstring(L, GetObjPtr<irr::scene::ISceneNode>(L)->getName());
	return 1;
}

int getBoundingBox(lua_State* L)
{
	push_aabbox3df(L, GetObjPtr<irr::scene::ISceneNode>(L)->getBoundingBox());
	return 1;
}

int getAbsoluteTransformation(lua_State* L)
{
	irr::core::matrix4* mat = new irr::core::matrix4;
	*mat = GetObjPtr<irr::scene::ISceneNode>(L)->getAbsoluteTransformation();
	push_matrix4(L, mat);
	return 1;
}
