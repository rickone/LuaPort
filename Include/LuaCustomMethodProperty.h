#pragma once

/*
__index = function(tb)
end,

__newindex = function(tb)
end,
*/

LUA_PORT_NAMESPACE_BEGIN

template<>
class MemberMethod<int (*)(lua_State*)>
{
    typedef int (*Type)(lua_State*);
    Type mFunc;
public:

    explicit MemberMethod(Type pFunc) : mFunc(pFunc)
    {
    }

    static int create(lua_State* L, Type pFunc)
    {
        MemberMethod* pHandler = new MemberMethod(pFunc);
        lua_pushlightuserdata(L, pHandler);
        lua_pushcclosure(L, index, 1);
        return 1;
    }

    static int index(lua_State* L)
    {
        MemberMethod* pHandler = static_cast<MemberMethod*>(lua_touserdata(L, lua_upvalueindex(1)));

        lua_pushstring(L, MT_OBJECT);
        lua_rawget(L, 1); // t, __object

        lua_pushcclosure(L, pHandler->mFunc, 1);
        return 1;
    }
};

template<>
class MemberProperty<int (*)(lua_State*)>
{
    typedef int (*Type)(lua_State*);
    Type mFunc;
public:

    explicit MemberProperty(Type pFunc) : mFunc(pFunc)
    {
    }

    static int create(lua_State* L, Type pFunc)
    {
        MemberProperty* pHandler = new MemberProperty(pFunc);
        lua_pushlightuserdata(L, pHandler);
        lua_pushcclosure(L, index, 1);

        lua_pushlightuserdata(L, pHandler);
        lua_pushcclosure(L, newIndex, 1);
        return 2;
    }

    static int index(lua_State* L)
    {
        MemberProperty* pHandler = static_cast<MemberProperty*>(lua_touserdata(L, lua_upvalueindex(1)));

        lua_pushstring(L, MT_OBJECT);
        lua_rawget(L, 1); // t, __object

        lua_pushcclosure(L, pHandler->mFunc, 1);
        if (0 == lua_pcall(L, 0, 1, 0))
            return 1;

        return 0;
    }

    static int newIndex(lua_State* L)
    {
        MemberProperty* pHandler = static_cast<MemberProperty*>(lua_touserdata(L, lua_upvalueindex(1)));

        lua_pushstring(L, MT_OBJECT);
        lua_rawget(L, 1); // t, v, __object

        lua_pushcclosure(L, pHandler->mFunc, 1);
        lua_pushvalue(L, 2);
        if (0 == lua_pcall(L, 1, 0, 0))
            return 0;

        return 0;
    }
};

#define LUA_PORT_TO_CUSTOM(L) (lua_touserdata((L), lua_upvalueindex(1)))

LUA_PORT_NAMESPACE_END
