#include "lua_IrrAssimp.h"

#include <irrlicht.h>
#include <IrrAssimp.h>

#include "lua_util.h"


int new_IrrAssimpImport(lua_State* L);

void init_IrrAssimp(lua_State* L)
{
	//lua_createtable(L, 0, 40);

	lua_pushcfunction(L, new_IrrAssimpImport);
	lua_setfield(L, -2, "new_IrrAssimpImport");
}

int push_IrrAssimpImport(lua_State* L, IrrAssimpImport* imp)
{
	CreateObjTable(L, imp);
	return 1;
}

int new_IrrAssimpImport(lua_State* L)
{
	push_IrrAssimpImport(L, new IrrAssimpImport(GetObjPtr<irr::scene::ISceneManager>(L, 2)));
	return 1;
}
