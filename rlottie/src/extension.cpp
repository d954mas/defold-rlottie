// myextension.cpp


// Extension lib defines
#define EXTENSION_NAME lottie
#define LIB_NAME "lottie"
#define MODULE_NAME "lottie"
// include the Defold SDK
#include <dmsdk/sdk.h>
#include "rlottie.h"
#include "rlottie_extension.h"
#include "rlottie_lua_bridge.h"
#include "vpoint.h"

using namespace luabridge;

static int LuaTest(lua_State* L){
    int width = (int)luaL_checknumber(L, 1);
    int height = (int)luaL_checknumber(L, 2);
    dmScript::LuaHBuffer* buffer = dmScript::CheckBuffer(L, 3);
    RlottieTest(width,height,buffer);

    return 0;
}

static rlottie::Animation* AnimationLoadFromData(lua_State* L){
    std::string name = luaL_checkstring(L, 1);
    std::string key = lua_tostring(L, 2);
    bool cachePolicy = lua_toboolean(L,3);
    std::unique_ptr<rlottie::Animation> animation = rlottie::Animation::loadFromData(name,key," ",cachePolicy);
    rlottie::Animation* animPointer = animation.release();
    return animPointer;
}

static rlottie::Surface SurfaceCreate(int w, int h, lua_State* L){
    dmScript::LuaHBuffer* lbuffer = dmScript::CheckBuffer(L, 3);
    Buffer buf = BufferCreate(w,h,4,lbuffer);
    rlottie::Surface surface(((uint32_t*)buf.stream), w, h ,  w * 4);
    return surface;
}

static void RlottieBind(lua_State* L){
     getGlobalNamespace (L)
        .beginNamespace ("rlottie")
        .addFunction ("test", LuaTest)
        .beginClass<VSize>("VSize")
            .addProperty ("w", &VSize::width,&VSize::setWidth)
            .addProperty ("h", &VSize::height,&VSize::setHeight)
        .endClass()
        .beginClass<rlottie::Animation>("Animation")
            //@DEFOLD not compile
            //.addFunction ("size", &rlottie::Animation::size)
            .addFunction ("duration", &rlottie::Animation::duration)
            .addFunction ("frameRate", &rlottie::Animation::frameRate)
            .addFunction ("totalFrame", &rlottie::Animation::totalFrame)
            .addFunction ("frameAtPos", &rlottie::Animation::frameAtPos)
            .addFunction ("renderSync", &rlottie::Animation::renderSync)
        .endClass()
        .beginClass<rlottie::Surface>("Surface")
            .addProperty ("width", &rlottie::Surface::width)
        .endClass()
        .addFunction("animation_load_from_data", &AnimationLoadFromData)
        .addFunction("surface_create", &SurfaceCreate)
        .endNamespace ();
}

static void LuaInit(lua_State* L){
	RlottieBind(L);
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