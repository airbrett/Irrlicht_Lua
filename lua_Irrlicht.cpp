#include "lua_IrrlichtDevice.h"
#include "EventReceiver.h"
#include "lua_ISceneNodeAnimator.h"
#include "lua_Plane.h"
#include "lua_IAttributes.h"
#include "lua_ISceneNode.h"
#include "lua_util.h"
#include "lua_IMeshBuffer.h"
#include "lua_ICameraSceneNode.h"
#include "lua_IrrAssimp.h"

#include <irrlicht.h>

#include "driverChoice.h"
#include "exampleHelper.h"

#include "lua.hpp"

#ifdef WIN32
#define IRRLICHT_LUA_EXPORT __declspec(dllexport)
#else
#define IRRLICHT_LUA_EXPORT
#endif

static int driverChoiceConsole(lua_State* L);
static int getExampleMediaPath(lua_State* L);
static int createDevice(lua_State* L);


extern "C" IRRLICHT_LUA_EXPORT int luaopen_irrlicht_lua(lua_State* L)
{
	std::cout << "luaopen_IrrLicht" << std::endl;
	lua_createtable(L, 0, 40);

	lua_pushcfunction(L, driverChoiceConsole);
	lua_setfield(L, -2, "driverChoiceConsole");

	lua_pushcfunction(L, getExampleMediaPath);
	lua_setfield(L, -2, "getExampleMediaPath");

	lua_pushcfunction(L, createDevice);
	lua_setfield(L, -2, "createDevice");

	init_IrrAssimp(L);
	
	lua_pushinteger(L, irr::EET_MOUSE_INPUT_EVENT);
	lua_setfield(L, -2, "EET_MOUSE_INPUT_EVENT");
	lua_pushinteger(L, irr::EET_KEY_INPUT_EVENT);
	lua_setfield(L, -2, "EET_KEY_INPUT_EVENT");


	//core
	lua_createtable(L, 0, 4);
	init_Plane(L);
	lua_setfield(L, -2, "core");

	//video
	lua_createtable(L, 0, 15);

	lua_pushinteger(L, irr::video::EDT_NULL);
	lua_setfield(L, -2, "EDT_NULL");
	lua_pushinteger(L, irr::video::EDT_SOFTWARE);
	lua_setfield(L, -2, "EDT_SOFTWARE");
	lua_pushinteger(L, irr::video::EDT_BURNINGSVIDEO);
	lua_setfield(L, -2, "EDT_BURNINGSVIDEO");
	lua_pushinteger(L, irr::video::EDT_DIRECT3D9);
	lua_setfield(L, -2, "EDT_DIRECT3D9");
	lua_pushinteger(L, irr::video::EDT_OPENGL);
	lua_setfield(L, -2, "EDT_OPENGL");
	lua_pushinteger(L, irr::video::EDT_COUNT);
	lua_setfield(L, -2, "EDT_COUNT");

	lua_pushinteger(L, irr::video::ECBF_NONE);
	lua_setfield(L, -2, "ECBF_NONE");
	lua_pushinteger(L, irr::video::ECBF_COLOR);
	lua_setfield(L, -2, "ECBF_COLOR");
	lua_pushinteger(L, irr::video::ECBF_DEPTH);
	lua_setfield(L, -2, "ECBF_DEPTH");
	lua_pushinteger(L, irr::video::ECBF_STENCIL);
	lua_setfield(L, -2, "ECBF_STENCIL");
	lua_pushinteger(L, irr::video::ECBF_ALL);
	lua_setfield(L, -2, "ECBF_ALL");

	lua_pushinteger(L, irr::video::EMF_WIREFRAME);
	lua_setfield(L, -2, "EMF_WIREFRAME");
	lua_pushinteger(L, irr::video::EMF_POINTCLOUD);
	lua_setfield(L, -2, "EMF_POINTCLOUD");
	lua_pushinteger(L, irr::video::EMF_GOURAUD_SHADING);
	lua_setfield(L, -2, "EMF_GOURAUD_SHADING");
	lua_pushinteger(L, irr::video::EMF_LIGHTING);
	lua_setfield(L, -2, "EMF_LIGHTING");
	lua_pushinteger(L, irr::video::EMF_ZBUFFER);
	lua_setfield(L, -2, "EMF_ZBUFFER");
	lua_pushinteger(L, irr::video::EMF_ZWRITE_ENABLE);
	lua_setfield(L, -2, "EMF_ZWRITE_ENABLE");
	lua_pushinteger(L, irr::video::EMF_BACK_FACE_CULLING);
	lua_setfield(L, -2, "EMF_BACK_FACE_CULLING");
	lua_pushinteger(L, irr::video::EMF_FRONT_FACE_CULLING);
	lua_setfield(L, -2, "EMF_FRONT_FACE_CULLING");
	lua_pushinteger(L, irr::video::EMF_BILINEAR_FILTER);
	lua_setfield(L, -2, "EMF_BILINEAR_FILTER");
	lua_pushinteger(L, irr::video::EMF_TRILINEAR_FILTER);
	lua_setfield(L, -2, "EMF_TRILINEAR_FILTER");
	lua_pushinteger(L, irr::video::EMF_ANISOTROPIC_FILTER);
	lua_setfield(L, -2, "EMF_ANISOTROPIC_FILTER");
	lua_pushinteger(L, irr::video::EMF_FOG_ENABLE);
	lua_setfield(L, -2, "EMF_FOG_ENABLE");
	lua_pushinteger(L, irr::video::EMF_NORMALIZE_NORMALS);
	lua_setfield(L, -2, "EMF_NORMALIZE_NORMALS");
	lua_pushinteger(L, irr::video::EMF_TEXTURE_WRAP);
	lua_setfield(L, -2, "EMF_TEXTURE_WRAP");
	lua_pushinteger(L, irr::video::EMF_ANTI_ALIASING);
	lua_setfield(L, -2, "EMF_ANTI_ALIASING");
	lua_pushinteger(L, irr::video::EMF_COLOR_MASK);
	lua_setfield(L, -2, "EMF_COLOR_MASK");
	lua_pushinteger(L, irr::video::EMF_COLOR_MATERIAL);
	lua_setfield(L, -2, "EMF_COLOR_MATERIAL");
	lua_pushinteger(L, irr::video::EMF_USE_MIP_MAPS);
	lua_setfield(L, -2, "EMF_USE_MIP_MAPS");
	lua_pushinteger(L, irr::video::EMF_BLEND_OPERATION);
	lua_setfield(L, -2, "EMF_BLEND_OPERATION");
	lua_pushinteger(L, irr::video::EMF_POLYGON_OFFSET);
	lua_setfield(L, -2, "EMF_POLYGON_OFFSET");
	lua_pushinteger(L, irr::video::EMF_BLEND_FACTOR);
	lua_setfield(L, -2, "EMF_BLEND_FACTOR");

	lua_pushinteger(L, irr::video::EMT_SOLID);
	lua_setfield(L, -2, "EMT_SOLID");
	lua_pushinteger(L, irr::video::EMT_SOLID_2_LAYER);
	lua_setfield(L, -2, "EMT_SOLID_2_LAYER");
	lua_pushinteger(L, irr::video::EMT_LIGHTMAP);
	lua_setfield(L, -2, "EMT_LIGHTMAP");
	lua_pushinteger(L, irr::video::EMT_LIGHTMAP_ADD);
	lua_setfield(L, -2, "EMT_LIGHTMAP_ADD");
	lua_pushinteger(L, irr::video::EMT_LIGHTMAP_M2);
	lua_setfield(L, -2, "EMT_LIGHTMAP_M2");
	lua_pushinteger(L, irr::video::EMT_LIGHTMAP_M4);
	lua_setfield(L, -2, "EMT_LIGHTMAP_M4");
	lua_pushinteger(L, irr::video::EMT_LIGHTMAP_LIGHTING);
	lua_setfield(L, -2, "EMT_LIGHTMAP_LIGHTING");
	lua_pushinteger(L, irr::video::EMT_LIGHTMAP_LIGHTING_M2);
	lua_setfield(L, -2, "EMT_LIGHTMAP_LIGHTING_M2");
	lua_pushinteger(L, irr::video::EMT_LIGHTMAP_LIGHTING_M4);
	lua_setfield(L, -2, "EMT_LIGHTMAP_LIGHTING_M4");
	lua_pushinteger(L, irr::video::EMT_DETAIL_MAP);
	lua_setfield(L, -2, "EMT_DETAIL_MAP");
	lua_pushinteger(L, irr::video::EMT_SPHERE_MAP);
	lua_setfield(L, -2, "EMT_SPHERE_MAP");
	lua_pushinteger(L, irr::video::EMT_REFLECTION_2_LAYER);
	lua_setfield(L, -2, "EMT_REFLECTION_2_LAYER");
	lua_pushinteger(L, irr::video::EMT_TRANSPARENT_ADD_COLOR);
	lua_setfield(L, -2, "EMT_TRANSPARENT_ADD_COLOR");
	lua_pushinteger(L, irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);
	lua_setfield(L, -2, "EMT_TRANSPARENT_ALPHA_CHANNEL");
	lua_pushinteger(L, irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF);
	lua_setfield(L, -2, "EMT_TRANSPARENT_ALPHA_CHANNEL_REF");
	lua_pushinteger(L, irr::video::EMT_TRANSPARENT_VERTEX_ALPHA);
	lua_setfield(L, -2, "EMT_TRANSPARENT_VERTEX_ALPHA");
	lua_pushinteger(L, irr::video::EMT_TRANSPARENT_REFLECTION_2_LAYER);
	lua_setfield(L, -2, "EMT_TRANSPARENT_REFLECTION_2_LAYER");
	lua_pushinteger(L, irr::video::EMT_NORMAL_MAP_SOLID);
	lua_setfield(L, -2, "EMT_NORMAL_MAP_SOLID");
	lua_pushinteger(L, irr::video::EMT_NORMAL_MAP_TRANSPARENT_ADD_COLOR);
	lua_setfield(L, -2, "EMT_NORMAL_MAP_TRANSPARENT_ADD_COLOR");
	lua_pushinteger(L, irr::video::EMT_NORMAL_MAP_TRANSPARENT_VERTEX_ALPHA);
	lua_setfield(L, -2, "EMT_NORMAL_MAP_TRANSPARENT_VERTEX_ALPHA");
	lua_pushinteger(L, irr::video::EMT_PARALLAX_MAP_SOLID);
	lua_setfield(L, -2, "EMT_PARALLAX_MAP_SOLID");
	lua_pushinteger(L, irr::video::EMT_PARALLAX_MAP_TRANSPARENT_ADD_COLOR);
	lua_setfield(L, -2, "EMT_PARALLAX_MAP_TRANSPARENT_ADD_COLOR");
	lua_pushinteger(L, irr::video::EMT_PARALLAX_MAP_TRANSPARENT_VERTEX_ALPHA);
	lua_setfield(L, -2, "EMT_PARALLAX_MAP_TRANSPARENT_VERTEX_ALPHA");
	lua_pushinteger(L, irr::video::EMT_ONETEXTURE_BLEND);
	lua_setfield(L, -2, "EMT_ONETEXTURE_BLEND");

	lua_pushinteger(L, irr::video::EVT_STANDARD);
	lua_setfield(L, -2, "EVT_STANDARD");
	lua_pushinteger(L, irr::video::EVT_2TCOORDS);
	lua_setfield(L, -2, "EVT_2TCOORDS");
	lua_pushinteger(L, irr::video::EVT_TANGENTS);
	lua_setfield(L, -2, "EVT_TANGENTS");

	lua_setfield(L, -2, "video");

	//scene
	lua_createtable(L, 0, 4);
	init_ISceneNode(L);
	init_IMeshBuffer(L);
	init_ICameraSceneNode(L);

	lua_pushstring(L, irr::scene::COLLADA_CREATE_SCENE_INSTANCES);
	lua_setfield(L, -2, "COLLADA_CREATE_SCENE_INSTANCES");

	lua_pushinteger(L, irr::scene::EDS_OFF);
	lua_setfield(L, -2, "EDS_OFF");
	lua_pushinteger(L, irr::scene::EDS_BBOX);
	lua_setfield(L, -2, "EDS_BBOX");
	lua_pushinteger(L, irr::scene::EDS_NORMALS);
	lua_setfield(L, -2, "EDS_NORMALS");
	lua_pushinteger(L, irr::scene::EDS_SKELETON);
	lua_setfield(L, -2, "EDS_SKELETON");
	lua_pushinteger(L, irr::scene::EDS_MESH_WIRE_OVERLAY);
	lua_setfield(L, -2, "EDS_MESH_WIRE_OVERLAY");
	lua_pushinteger(L, irr::scene::EDS_HALF_TRANSPARENCY);
	lua_setfield(L, -2, "EDS_HALF_TRANSPARENCY");
	lua_pushinteger(L, irr::scene::EDS_BBOX_BUFFERS);
	lua_setfield(L, -2, "EDS_BBOX_BUFFERS");
	lua_pushinteger(L, irr::scene::EDS_BBOX_ALL);
	lua_setfield(L, -2, "EDS_BBOX_ALL");
	lua_pushinteger(L, irr::scene::EDS_FULL);
	lua_setfield(L, -2, "EDS_FULL");

	lua_setfield(L, -2, "scene");

	//io
	lua_createtable(L, 0, 4);
	init_IAttributes(L);
	lua_setfield(L, -2, "io");

	return 1;
}



int driverChoiceConsole(lua_State* L)
{
	irr::video::E_DRIVER_TYPE driverType = irr::driverChoiceConsole(check_boolean(L, 1));
	lua_pushinteger(L, driverType);

	return 1;
}

int getExampleMediaPath(lua_State* L)
{
	lua_pushstring(L, irr::getExampleMediaPath().c_str());

	return 1;
}

int createDevice(lua_State* L)
{
	irr::video::E_DRIVER_TYPE driverType = irr::video::EDT_SOFTWARE;

	if (lua_gettop(L) > 0)
		driverType = static_cast<irr::video::E_DRIVER_TYPE>(luaL_checkinteger(L, 1));

	irr::core::dimension2d<irr::u32> windowSize(640, 480);

	if (lua_gettop(L) > 1)
		windowSize = check_dimension2d(L, 2);

	irr::u32 bits = 32;

	if (lua_gettop(L) > 2)
		bits = static_cast<irr::u32>(luaL_checkinteger(L, 3));

	bool fullscreen = false;

	if (lua_gettop(L) > 3)
		fullscreen = check_boolean(L, 4);

	bool stencilbuffer = false;

	if (lua_gettop(L) > 4)
		stencilbuffer = check_boolean(L, 5);

	bool vsync = false;

	if (lua_gettop(L) > 5)
		vsync = check_boolean(L, 6);

	EventReceiver* Receiver = nullptr;

	if (lua_gettop(L) > 6)
	{
		int ref = luaL_ref(L, LUA_REGISTRYINDEX);
		Receiver = new EventReceiver(L, ref);
	}

	irr::IrrlichtDevice* device = irr::createDevice(driverType, windowSize, bits, fullscreen, stencilbuffer, vsync, Receiver);
	push_IrrlichtDevice(L, device);

	return 1;
}
