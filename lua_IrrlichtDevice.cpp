#include "lua_IrrlichtDevice.h"

#include "lua_util.h"
#include "lua_IVideoDriver.h"
#include "lua_ISceneManager.h"
#include "lua_IFileSystem.h"
#include "lua_ICursorControl.h"
#include "lua_ITimer.h"

const static char* MetaTableName = "__dev_meta";

static int run(lua_State* L);
static int isWindowActive(lua_State* L);
static int yield(lua_State* L);
static int setWindowCaption(lua_State* L);
static int gc(lua_State* L);

void init_IrrlichtDevice(lua_State* L)
{
	lua_createtable(L, 0, 10);

	lua_pushcfunction(L, run);
	lua_setfield(L, -2, "run");

	lua_pushcfunction(L, isWindowActive);
	lua_setfield(L, -2, "isWindowActive");

	lua_pushcfunction(L, yield);
	lua_setfield(L, -2, "yield");

	lua_pushcfunction(L, setWindowCaption);
	lua_setfield(L, -2, "setWindowCaption");

	lua_pushcfunction(L, gc);
	lua_setfield(L, -2, "delete");
	
	luaL_newmetatable(L, MetaTableName);
	lua_pushcfunction(L, gc);
	lua_setfield(L, -2, "__gc");

	lua_pushvalue(L, -2);
	lua_setfield(L, -2, "__index");
	lua_pop(L, 2);
}

void push_IrrlichtDevice(lua_State* L, irr::IrrlichtDevice* device)
{
	CreateObjTable(L, device);

	luaL_setmetatable(L, MetaTableName);

	push_IVideoDriver(L, device->getVideoDriver());
	lua_setfield(L, -2, "videoDriver");

	push_ISceneManager(L, device->getSceneManager());
	lua_setfield(L, -2, "sceneManager");

	push_IrrFileSystem(L, device->getFileSystem());
	lua_setfield(L, -2, "fileSystem");

	push_ICursorControl(L, device->getCursorControl());
	lua_setfield(L, -2, "cursorControl");

	push_ITimer(L, device->getTimer());
	lua_setfield(L, -2, "timer");
}

static int run(lua_State* L)
{
	lua_pushboolean(L, GetObjPtr<irr::IrrlichtDevice>(L)->run());

	return 1;
}

static int isWindowActive(lua_State* L)
{
	lua_pushboolean(L, GetObjPtr<irr::IrrlichtDevice>(L)->isWindowActive());

	return 1;
}

static int yield(lua_State* L)
{
	GetObjPtr<irr::IrrlichtDevice>(L)->yield();

	return 0;
}

int setWindowCaption(lua_State* L)
{
	const wchar_t* Name = char_to_wchar(luaL_checkstring(L, 2));

    GetObjPtr<irr::IrrlichtDevice>(L)->setWindowCaption(Name);
    delete Name;
    return 0;
}

int gc(lua_State* L)
{
	lua_getfield(L, -1, "deleted");
	bool deleted = lua_toboolean(L, -1);

	if (!deleted)
	{
		delete GetObjPtr<irr::IrrlichtDevice>(L);

		lua_pushboolean(L, true);
		lua_setfield(L, -2, "deleted");
	}

	return 0;
}
