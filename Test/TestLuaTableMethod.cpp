#include "stdafx.h"
#include <math.h>

int Foo3(float x, float y)
{
    return (int)sqrt(x * x + y * y);
}

int Foo4(lua_State* L)
{
    float a = (float)lua_tonumber(L, 1);
    lua_pushnumber(L, sqrt(a));
    return 1;
}

int TestLuaTableMethod(lua_State* L)
{
    int nResult = true;
    const char* pszScript = "return Lib.Foo3(3, 4) + Foo4(100);";

    LuaPort::addTableMethod(L, "Lib", "Foo3", &Foo3);
    LuaPort::addTableMethod(L, "_G", "Foo4", &Foo4);
    
    if (0 != luaL_dostring(L, pszScript))
    {
        nResult = false;
        printf("Lua error: %s\n", lua_tostring(L, -1));
    }
    else
    {
        int nRetCode = lua_tointeger(L, -1);
        if (nRetCode != 15)
            nResult = false;
    }

    return nResult;
}
