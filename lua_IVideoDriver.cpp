#include "lua_IVideoDriver.h"

#include "lua_util.h"

static int beginScene(lua_State* L);
static int endScene(lua_State* L);
static int getFPS(lua_State* L);
static int getName(lua_State* L);

void push_IVideoDriver(lua_State* L, irr::video::IVideoDriver* driver)
{
	CreateObjTable(L, driver);

	lua_pushcfunction(L, beginScene);
	lua_setfield(L, -2, "beginScene");
	lua_pushcfunction(L, endScene);
	lua_setfield(L, -2, "endScene");
	lua_pushcfunction(L, getFPS);
	lua_setfield(L, -2, "getFPS");
    lua_pushcfunction(L, getName);
    lua_setfield(L, -2, "getName");
}

int beginScene(lua_State* L)
{
	GetObjPtr<irr::video::IVideoDriver>(L)->beginScene(luaL_checkinteger(L, 2), check_scolor(L, 3));
	return 0;
}

int endScene(lua_State* L)
{
	GetObjPtr<irr::video::IVideoDriver>(L)->endScene();
	return 0;
}

int getFPS(lua_State* L)
{
	lua_pushinteger(L, GetObjPtr<irr::video::IVideoDriver>(L)->getFPS());
	return 1;
}

int getName(lua_State* L)
{
    char* Name = wchar_to_char(GetObjPtr<irr::video::IVideoDriver>(L)->getName());
    lua_pushstring(L, Name);
    delete Name;
	return 1;
}
