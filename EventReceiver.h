#pragma once
#include <irrlicht.h>
#include <lua.hpp>

class EventReceiver : public irr::IEventReceiver
{
private:
    lua_State* mL;
    int mRef;

public:
    EventReceiver(lua_State* L, const int ref);

    virtual bool OnEvent(const irr::SEvent& event);
};