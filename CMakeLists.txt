cmake_minimum_required (VERSION 3.8)

project (irrlicht_lua)

set (CMAKE_CXX_STANDARD 11)

find_package(Lua REQUIRED)
find_package(Irrlicht REQUIRED)
find_package(Assimp REQUIRED)
find_package(IrrAssimp REQUIRED)

add_library(irrlicht_lua SHARED
	lua_Irrlicht.cpp
	lua_IrrlichtDevice.h
	lua_IrrlichtDevice.cpp
	lua_IrrAssimp.h
	lua_IrrAssimp.cpp
	lua_ISceneManager.h
	lua_ISceneManager.cpp
	lua_ISceneNode.h
	lua_ISceneNode.cpp
	lua_ISceneNodeAnimator.h
	lua_ISceneNodeAnimator.cpp
	lua_IAnimatedMesh.h
	lua_IAnimatedMesh.cpp
	lua_IAnimatedMeshSceneNode.h
	lua_IAnimatedMeshSceneNode.cpp
	lua_IAttributes.h
	lua_IAttributes.cpp
	lua_ICameraSceneNode.h
	lua_ICameraSceneNode.cpp
	lua_ICursorControl.h
	lua_ICursorControl.cpp
	EventReceiver.h
	EventReceiver.cpp
	lua_IFileSystem.h
	lua_IFileSystem.cpp
	lua_ILightSceneNode.h
	lua_ILightSceneNode.cpp
	lua_IMesh.h
	lua_IMesh.cpp
	lua_IMeshBuffer.h
	lua_IMeshBuffer.cpp
	lua_ITimer.h
	lua_ITimer.cpp
	lua_IVideoDriver.h
	lua_IVideoDriver.cpp
	lua_Plane.h
	lua_Plane.cpp
	lua_util.h
	lua_util.cpp
	SceneNodeAnimator.h
	SceneNodeAnimator.cpp
)

set_target_properties(irrlicht_lua PROPERTIES PREFIX "")

target_compile_definitions(irrlicht_lua
	PRIVATE WIN32_LEAN_AND_MEAN
	PRIVATE NOMINMAX
)

target_include_directories(irrlicht_lua PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	${LUA_INCLUDE_DIR}
)

target_link_libraries(irrlicht_lua
	${LUA_LIBRARIES}
	Irrlicht
	assimp::assimp
	IrrAssimp
)

