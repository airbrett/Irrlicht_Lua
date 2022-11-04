#include "EventReceiver.h"

#include "lua_util.h"

EventReceiver::EventReceiver(lua_State* L, const int ref) :
    mL(L),
    mRef(ref)
{
}

bool EventReceiver::OnEvent(const irr::SEvent& event)
{
    lua_rawgeti(mL, LUA_REGISTRYINDEX, mRef);
    const int Table = lua_gettop(mL);

    lua_getfield(mL, -1, "OnEvent");

    lua_pushvalue(mL, Table);

    lua_createtable(mL, 0, 4);

    lua_pushinteger(mL, event.EventType);
    lua_setfield(mL, -2, "Type");

    switch (event.EventType)
    {
    case irr::EET_KEY_INPUT_EVENT:
        lua_pushinteger(mL, event.KeyInput.Key);
        lua_setfield(mL, -2, "Key");

        lua_pushboolean(mL, event.KeyInput.PressedDown);
        lua_setfield(mL, -2, "PressedDown");
        break;
    case irr::EET_MOUSE_INPUT_EVENT:
        lua_pushinteger(mL, event.MouseInput.X);
        lua_setfield(mL, -2, "x");

        lua_pushinteger(mL, event.MouseInput.Y);
        lua_setfield(mL, -2, "y");

        lua_pushboolean(mL, event.MouseInput.isLeftPressed());
        lua_setfield(mL, -2, "leftPressed");
        break;
    }

    lua_call(mL, 2, 1);

    return check_boolean(mL, -1);
}
