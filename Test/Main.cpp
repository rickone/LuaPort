#include "stdafx.h"

#define TEST_CASE(Case) \
    { \
        int Test##Case(lua_State*); \
        int nTop = lua_gettop(L); \
        int bRet = Test##Case(L); \
        if (bRet) \
            nSuccessCount++; \
        else \
            nFailedCount++; \
        printf(">Test '%s' ... ... [%s]\n", #Case, bRet ? "Success" : "Failed"); \
        lua_settop(L, nTop); \
    }

int main(int argc, char* argv[])
{
    int nSuccessCount = 0;
    int nFailedCount = 0;
    lua_State* L = luaL_newstate();

    luaL_openlibs(L);

    TEST_CASE(LuaBridge);
    TEST_CASE(LuaClassExport);
    TEST_CASE(LuaTableMethod);

    printf(">>Done! Success %d, Failed %d\n", nSuccessCount, nFailedCount);

    lua_close(L);
    return 0;
}

