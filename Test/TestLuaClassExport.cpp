#include "stdafx.h"

class TestBase
{
public:
    TestBase() : x(0) {}
    virtual ~TestBase() {}

    virtual int Foo(int a)
    {
        return a * a;
    }

    int x;
};

class TestXX : public TestBase
{
public:
    virtual int Foo(int a)
    {
        return a + a;
    }

    int Foo3(lua_State* L)
    {
        int a = (int)lua_tointeger(L, 1);
        lua_pushinteger(L, a * 2);
        return 1;
    }
};

LUA_PORT_CLASS(TestBase);
LUA_PORT_CLASS(TestXX);

int Foo2(lua_State* L)
{
    TestXX* pObj = (TestXX*)LUA_PORT_TO_CUSTOM(L);
    int a = LuaPort::LuaTo<int>(L, 1);
    int b = LuaPort::LuaTo<int>(L, 2);

    lua_pushinteger(L, pObj->Foo(a) + b);
    return 1;
}

int Prop(lua_State* L)
{
    int nTop = lua_gettop(L);
    TestXX* pObj = (TestXX*)LUA_PORT_TO_CUSTOM(L);
    if (nTop == 0)
    {
        // index
        lua_pushinteger(L, pObj->x * 2);
        return 1;
    }
    else if (nTop == 1)
    {
        // newindex
        int nValue = (int)lua_tointeger(L, 1);
        pObj->x = nValue / 2;
    }
    return 0;
}

void* TestXX2TestBase(void* pvObj)
{
    TestXX* pObjSrc = static_cast<TestXX*>(pvObj);
    TestBase* pObjDst = dynamic_cast<TestBase*>(pObjSrc);
    return pObjDst;
}

int TestLuaClassExport(lua_State* L)
{
    int nResult = true;

    TestXX obj;
    const char* pszScript =
        "function Test(obj, a)"
        "   obj.x = obj.Foo2(a, 100) + obj.Foo3(a);"
        "   obj.Prop = obj.Prop - 201;"
        "   return obj.x;"
        "end";

    luaL_dostring(L, pszScript);

    LUA_PORT_EXPORT_CREATE(L, TestBase);
    LUA_PORT_EXPORT_PROPERTY(L, TestBase, x);
    LUA_PORT_EXPORT_METHOD(L, TestBase, Foo);

    LuaPort::ClassExport<TestXX>::create(L);
    LuaPort::ClassExport<TestXX>::addMemberMethod(L, "Foo2", &Foo2);
    LuaPort::ClassExport<TestXX>::addMemberMethod(L, "Foo3", &TestXX::Foo3);
    LuaPort::ClassExport<TestXX>::addMemberProperty(L, "Prop", &Prop);

    LUA_PORT_INHERIT(L, TestXX, TestBase);

    lua_getglobal(L, "Test");
    LuaPort::pushObject(L, &obj);
    lua_pushinteger(L, 100);
    if (0 != lua_pcall(L, 2, 1, 0))
    {
        nResult = false;
        printf("Lua error: %s\n", lua_tostring(L, -1));
    }
    else
    {
        int nRetCode = lua_tointeger(L, -1);
        if (nRetCode != 399)
            nResult = false;
    }

    return nResult;
}
