#include "lua_IAnimatedMesh.h"


#include "lua_util.h"

const static char* MetaTableName = "__IMeshBuffer_meta";

static int getVertexType(lua_State* L);
static int getVertex(lua_State* L);
static int getVertexCount(lua_State* L);
static int getIndexCount(lua_State* L);
static int getIndex(lua_State* L);

void init_IMeshBuffer(lua_State* L)
{
	lua_createtable(L, 0, 5);

	lua_pushcfunction(L, getVertexType);
	lua_setfield(L, -2, "getVertexType");

	lua_pushcfunction(L, getVertex);
	lua_setfield(L, -2, "getVertex");

	lua_pushcfunction(L, getVertexCount);
	lua_setfield(L, -2, "getVertexCount");

	lua_pushcfunction(L, getIndexCount);
	lua_setfield(L, -2, "getIndexCount");

	lua_pushcfunction(L, getIndex);
	lua_setfield(L, -2, "getIndex");

	luaL_newmetatable(L, MetaTableName);
	lua_pushvalue(L, -2);
	lua_setfield(L, -2, "__index");
	lua_pop(L, 2);
}

void push_IMeshBuffer(lua_State* L, irr::scene::IMeshBuffer* imb)
{
	CreateObjTable(L, imb);

	luaL_setmetatable(L, MetaTableName);
}

int getVertexType(lua_State* L)
{
	const irr::video::E_VERTEX_TYPE type = GetObjPtr<irr::scene::IMeshBuffer>(L)->getVertexType();
	lua_pushinteger(L, static_cast<lua_Integer>(type));
	return 1;
}

int getVertex(lua_State* L)
{
	irr::scene::IMeshBuffer* imb = GetObjPtr<irr::scene::IMeshBuffer>(L);
	const irr::u32 index = static_cast<irr::u32>(luaL_checkinteger(L, 2));

	lua_createtable(L, 0, 5);

	switch (imb->getVertexType())
	{
	case irr::video::EVT_STANDARD:
	{
		const irr::video::S3DVertex& vtx = reinterpret_cast<irr::video::S3DVertex*>(imb->getVertices())[index];
		push_scolor(L, vtx.Color);
		lua_setfield(L, -2, "Color");

		push_vector3df(L, vtx.Normal);
		lua_setfield(L, -2, "Normal");

		push_vector3df(L, vtx.Pos);
		lua_setfield(L, -2, "Pos");

		push_vector2df(L, vtx.TCoords);
		lua_setfield(L, -2, "TCoords");

		break;
	}
	case irr::video::EVT_2TCOORDS:
		break;
	case irr::video::EVT_TANGENTS:
		break;
	}
	
	return 1;
}

int getVertexCount(lua_State* L)
{
	lua_pushinteger(L, static_cast<lua_Integer>(GetObjPtr<irr::scene::IMeshBuffer>(L)->getVertexCount()));
	return 1;
}

int getIndexCount(lua_State* L)
{
	lua_pushinteger(L, static_cast<lua_Integer>(GetObjPtr<irr::scene::IMeshBuffer>(L)->getIndexCount()));
	return 1;
}

int getIndex(lua_State* L)
{
	irr::u16 idx = GetObjPtr<irr::scene::IMeshBuffer>(L)->getIndices()[luaL_checkinteger(L, 2)];
	lua_pushinteger(L, idx);
	return 1;
}
