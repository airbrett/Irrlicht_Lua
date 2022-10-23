#include "lua_ITimer.h"

#include "lua_util.h"

static int getRealTime(lua_State* L);

void push_ITimer(lua_State* L, irr::ITimer* timer)
{
	CreateObjTable(L, timer);

	lua_pushcfunction(L, getRealTime);
	lua_setfield(L, -2, "getRealTime");
}

int getRealTime(lua_State* L)
{
	lua_pushinteger(L, GetObjPtr<irr::ITimer>(L)->getRealTime());
	return 1;
}
