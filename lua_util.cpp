#include "lua_util.h"

irr::core::vector3df check_vector3df(lua_State* L, const int n)
{
	irr::core::vector3df vec;

	luaL_checktype(L, n, LUA_TTABLE);

	lua_getfield(L, n, "X");
	vec.X = static_cast<float>(luaL_checknumber(L, -1));
	lua_pop(L, 1);

	lua_getfield(L, n, "Y");
	vec.Y = static_cast<float>(luaL_checknumber(L, -1));
	lua_pop(L, 1);

	lua_getfield(L, n, "Z");
	vec.Z = static_cast<float>(luaL_checknumber(L, -1));
	lua_pop(L, 1);

	return vec;
}

void push_vector3df(lua_State* L, irr::core::vector3df vec)
{
	lua_createtable(L, 0, 3);
	lua_pushnumber(L, vec.X);
	lua_setfield(L, -2, "X");

	lua_pushnumber(L, vec.Y);
	lua_setfield(L, -2, "Y");

	lua_pushnumber(L, vec.Z);
	lua_setfield(L, -2, "Z");
}

irr::core::vector2df check_vector2df(lua_State* L, const int n)
{
	irr::core::vector2df vec;

	luaL_checktype(L, n, LUA_TTABLE);

	lua_getfield(L, n, "X");
	vec.X = static_cast<float>(luaL_checknumber(L, -1));
	lua_pop(L, 1);

	lua_getfield(L, n, "Y");
	vec.Y = static_cast<float>(luaL_checknumber(L, -1));
	lua_pop(L, 1);

	return vec;
}

void push_vector2df(lua_State* L, irr::core::vector2df vec)
{
	lua_createtable(L, 0, 3);
	lua_pushnumber(L, vec.X);
	lua_setfield(L, -2, "X");

	lua_pushnumber(L, vec.Y);
	lua_setfield(L, -2, "Y");
}

irr::core::vector2di check_vector2di(lua_State* L, const int n)
{
	irr::core::vector2di vec;

	luaL_checktype(L, n, LUA_TTABLE);

	lua_getfield(L, n, "X");
	vec.X = static_cast<irr::s32>(luaL_checkinteger(L, -1));
	lua_pop(L, 1);

	lua_getfield(L, n, "Y");
	vec.Y = static_cast<irr::s32>(luaL_checkinteger(L, -1));
	lua_pop(L, 1);

	return vec;
}


void push_vector2di(lua_State* L, irr::core::vector2di vec)
{
	lua_createtable(L, 0, 3);
	lua_pushinteger(L, vec.X);
	lua_setfield(L, -2, "X");

	lua_pushinteger(L, vec.Y);
	lua_setfield(L, -2, "Y");
}

irr::video::SColor check_scolor(lua_State* L, const int n)
{
	luaL_checktype(L, n, LUA_TTABLE);

	lua_getfield(L, n, "a");
	const irr::u32 a = static_cast<irr::u32>(luaL_checkinteger(L, -1));
	lua_pop(L, 1);

	lua_getfield(L, n, "r");
	const irr::u32 r = static_cast<irr::u32>(luaL_checkinteger(L, -1));
	lua_pop(L, 1);

	lua_getfield(L, n, "g");
	const irr::u32 g = static_cast<irr::u32>(luaL_checkinteger(L, -1));
	lua_pop(L, 1);

	lua_getfield(L, n, "b");
	const irr::u32 b = static_cast<irr::u32>(luaL_checkinteger(L, -1));
	lua_pop(L, 1);

	return irr::video::SColor(a, r, g, b);
}

void push_scolor(lua_State* L, irr::video::SColor vec)
{
	lua_createtable(L, 0, 3);

	lua_pushinteger(L, vec.getAlpha());
	lua_setfield(L, -2, "a");

	lua_pushinteger(L, vec.getRed());
	lua_setfield(L, -2, "r");

	lua_pushinteger(L, vec.getGreen());
	lua_setfield(L, -2, "g");

	lua_pushinteger(L, vec.getBlue());
	lua_setfield(L, -2, "b");
}

irr::video::SColorf check_scolorf(lua_State* L, const int n)
{
	luaL_checktype(L, n, LUA_TTABLE);

	lua_getfield(L, n, "r");
	const irr::f32 r = static_cast<irr::f32>(luaL_checknumber(L, -1));
	lua_pop(L, 1);

	lua_getfield(L, n, "g");
	const irr::f32 g = static_cast<irr::f32>(luaL_checknumber(L, -1));
	lua_pop(L, 1);

	lua_getfield(L, n, "b");
	const irr::f32 b = static_cast<irr::f32>(luaL_checknumber(L, -1));
	lua_pop(L, 1);

	return irr::video::SColorf(r, g, b);
}

irr::core::dimension2d<irr::u32> check_dimension2d(lua_State* L, const int n)
{
	luaL_checktype(L, n, LUA_TTABLE);

	lua_getfield(L, n, "w");
	const irr::u32 w = static_cast<irr::u32>(luaL_checkinteger(L, -1));
	lua_pop(L, 1);

	lua_getfield(L, n, "h");
	const irr::u32 h = static_cast<irr::u32>(luaL_checkinteger(L, -1));
	lua_pop(L, 1);

	return irr::core::dimension2d<irr::u32>(w, h);
}

bool check_boolean(lua_State* L, const int n)
{
	if (!lua_isboolean(L, n))
		lua_error(L);

	return lua_toboolean(L, n);
}

char* wchar_to_char(const wchar_t* wc)
{
	size_t wlen = wcslen(wc) + 1;
	char* c = new char[wlen];
	wcstombs(c, wc, wlen);

	return c;
}

const wchar_t* char_to_wchar(const char* c)
{
	const size_t clen = strlen(c) + 1;
	wchar_t* wc = new wchar_t[clen];
	mbstowcs(wc, c, clen);

	return wc;
}