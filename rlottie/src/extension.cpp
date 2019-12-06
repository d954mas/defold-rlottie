// myextension.cpp
// Extension lib defines
#define EXTENSION_NAME lottie
#define LIB_NAME "lottie"
#define MODULE_NAME "lottie"
// include the Defold SDK
#include <dmsdk/sdk.h>
#include "rlottie.h"
#include "rlottie_extension.h"

static int LuaTest(lua_State* L){
    RlottieTest();
    printf("RLOTTIE\n");
    return 0;
}

// Functions exposed to Lua
static const luaL_reg Module_methods[] ={
	{"test", LuaTest},
	{0, 0}
};

static void LuaInit(lua_State* L){
	int top = lua_gettop(L);
	luaL_register(L, MODULE_NAME, Module_methods);
	lua_pop(L, 1);
	assert(top == lua_gettop(L));
}

static dmExtension::Result AppInitializeMyExtension(dmExtension::AppParams* params){return dmExtension::RESULT_OK;}
static dmExtension::Result InitializeMyExtension(dmExtension::Params* params){
	LuaInit(params->m_L);
	printf("Registered %s Extension\n", MODULE_NAME);
	return dmExtension::RESULT_OK;
}

static dmExtension::Result AppFinalizeMyExtension(dmExtension::AppParams* params){return dmExtension::RESULT_OK;}

static dmExtension::Result FinalizeMyExtension(dmExtension::Params* params){return dmExtension::RESULT_OK;}

DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, AppInitializeMyExtension, AppFinalizeMyExtension, InitializeMyExtension, 0, 0, FinalizeMyExtension)