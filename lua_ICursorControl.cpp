#include "lua_ICursorControl.h"

#include "lua_util.h"

static int setVisible(lua_State* L);
static int getRelativePosition(lua_State* L);
static int setPosition(lua_State* L);

void push_ICursorControl(lua_State* L, irr::gui::ICursorControl* cc)
{
	CreateObjTable(L, cc);

	lua_pushcfunction(L, setVisible);
	lua_setfield(L, -2, "setVisible");

	lua_pushcfunction(L, getRelativePosition);
	lua_setfield(L, -2, "getRelativePosition");

	lua_pushcfunction(L, setPosition);
	lua_setfield(L, -2, "setPosition");
}

int setVisible(lua_State* L)
{
	GetObjPtr<irr::gui::ICursorControl>(L)->setVisible(check_boolean(L, -1));

	return 0;
}

int getRelativePosition(lua_State* L)
{
	bool updateCursor = true;

	if (lua_gettop(L) > 1)
		updateCursor = lua_toboolean(L, 2);

	push_vector2df(L, GetObjPtr<irr::gui::ICursorControl>(L)->getRelativePosition(updateCursor));

	return 1;
}

int setPosition(lua_State* L)
{
	irr::gui::ICursorControl* cc = GetObjPtr<irr::gui::ICursorControl>(L);

	if (lua_istable(L, 2))
		cc->setPosition(check_vector2df(L, 2));
	else if (lua_isnumber(L, 2))
		cc->setPosition(static_cast<irr::f32>(luaL_checknumber(L, 2)), static_cast<irr::f32>(luaL_checknumber(L, 3)));
	else
		cc->setPosition(static_cast<irr::s32>(luaL_checkinteger(L, 2)), static_cast<irr::s32>(luaL_checkinteger(L, 3)));

	return 0;
}