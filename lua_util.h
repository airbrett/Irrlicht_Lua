#pragma once

#include <irrlicht.h>

#include <lua.hpp>

#include <typeinfo>
#include <iostream>
#include <stdexcept>

template<typename T>
T* GetObjPtr(lua_State* L, const int arg=1)
{
	luaL_checktype(L, arg, LUA_TTABLE);

	//lua_getfield(L, arg, "type");
	//std::type_info** type = reinterpret_cast<std::type_info**>(lua_touserdata(L, -1));
	//
	//if (*type != &typeid(T*))
	//{
	//	//std::cout << "got: " << *type << " expected: " << typeid(T*).hash_code() << std::endl;
	//	std::cout << "got: " << (*type)->name() << " expected: " << typeid(T*).name() << std::endl;
	//	throw std::runtime_error("type mismatch");
	//}

	lua_getfield(L, arg, "ptr");
	T* Obj = *reinterpret_cast<T**>(lua_touserdata(L, -1));

	//lua_pop(L, 2);
	lua_pop(L, 1);
	return Obj;
}

template<typename T>
void CreateObjTable(lua_State* L, T* Obj)
{
	lua_createtable(L, 0, 4);

	void* Ptr = lua_newuserdata(L, sizeof(Obj));
	*reinterpret_cast<T**>(Ptr) = Obj;
	lua_setfield(L, -2, "ptr");

	//void* Type = lua_newuserdata(L, sizeof(std::type_info*));
	//*reinterpret_cast<const std::type_info**>(Type) = &typeid(Obj);
	//lua_setfield(L, -2, "type");
}

irr::core::vector3df to_vector3df(lua_State* L, const int n);
irr::core::vector3df check_vector3df(lua_State* L, const int n);
void push_vector3df(lua_State* L, irr::core::vector3df vec);
irr::core::vector2df check_vector2df(lua_State* L, const int n);
void push_vector2df(lua_State* L, irr::core::vector2df vec);
irr::core::vector2di check_vector2di(lua_State* L, const int n);
void push_vector2di(lua_State* L, irr::core::vector2di vec);
irr::video::SColor check_scolor(lua_State* L, const int n);
void push_scolor(lua_State* L, irr::video::SColor vec);
irr::video::SColorf check_scolorf(lua_State* L, const int n);
irr::core::dimension2d<irr::u32> check_dimension2d(lua_State* L, const int n);
bool check_boolean(lua_State* L, const int n);
void push_aabbox3df(lua_State* L, const irr::core::aabbox3d<irr::f32>& bb);

#define push_s32(L, n) lua_pushinteger(L, n)
#define push_f32 lua_pushnumber(L, n)
#define check_s32(L, n) static_cast<irr::s32>(luaL_checkinteger(L, n))
#define check_u32(L, n) static_cast<irr::u32>(luaL_checkinteger(L, n))
#define check_f32(L, n) static_cast<irr::f32>(luaL_checknumber(L, n))
#define is_s32(L, n) lua_isinteger(L, n)
#define is_u32(L, n) lua_isinteger(L, n)
#define is_f32(L, n) lua_isnumber(L, n)
#define to_s32(L, n) lua_tointeger(L, n)
#define to_u32(L, n) lua_tointeger(L, n)
#define to_f32(L, n) lua_tonumber(L, n)

char* wchar_to_char(const wchar_t* pwchar);
const wchar_t* char_to_wchar(const char* c);
