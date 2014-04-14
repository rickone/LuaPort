#ifndef LUACG_IS_ITERATING

LUA_PORT_NAMESPACE_BEGIN

template<typename T>
class TableMethod;

#define n LUACG_ITERATOR()
#define repeat_f(_, n) LUACG_CAT(A, n) LUACG_CAT(a, n) = LuaTo<LUACG_CAT(A, n)>(L, LUACG_INC(n));

#define LUACG_ITERATOR_BEGIN    0
#define LUACG_ITERATOR_END      LUA_PORT_FUNC_PARAM_LIMITS
#define LUACG_ITERATE_FILE      "LuaTableMethod.h"
#include LUACG_ITERATE()

#undef repeat_f
#undef n

template<>
class TableMethod<int (*)(lua_State*)>
{
    typedef int (*Type)(lua_State*);
    Type mFunc;
public:

    explicit TableMethod(Type pFunc) : mFunc(pFunc)
    {
    }

    static int create(lua_State* L, Type pTableFunc)
    {
        TableMethod* pHandler = new TableMethod(pTableFunc);

        lua_pushlightuserdata(L, pHandler);
        lua_pushcclosure(L, index, 1);
        return 1;
    }

    static int index(lua_State* L)
    {
        TableMethod* pHandler = static_cast<TableMethod*>(lua_touserdata(L, lua_upvalueindex(1)));

        return (*pHandler->mFunc)(L);
    }
};

template<typename T>
void addTableMethod(lua_State* L, const char* pszTableName, const char* pszMethodName, T t)
{
    int nTop = lua_gettop(L);

    lua_getglobal(L, pszTableName);
    if (!lua_istable(L, -1))
    {
        lua_pop(L, 1);
        lua_newtable(L);

        lua_pushvalue(L, -1);
        lua_setglobal(L, pszTableName);
    }

    TableMethod<T>::create(L, t);
    lua_setfield(L, -2, pszMethodName);
    lua_settop(L, nTop);
}

LUA_PORT_NAMESPACE_END

#else // LUACG_IS_ITERATING

template<typename R LUACG_COMMA_IF(n) LUACG_ENUM_PARAMS(n, typename A)>
class TableMethod<R (*)(LUACG_ENUM_PARAMS(n, A))>
{
    typedef R (*Type)(LUACG_ENUM_PARAMS(n, A));
    Type mFunc;
public:

    explicit TableMethod(Type pFunc) : mFunc(pFunc)
    {
    }

    static int create(lua_State* L, Type pTableFunc)
    {
        TableMethod* pHandler = new TableMethod(pTableFunc);

        lua_pushlightuserdata(L, pHandler);
        lua_pushcclosure(L, index, 1);
        return 1;
    }

    static int index(lua_State* L)
    {
        TableMethod* pHandler = static_cast<TableMethod*>(lua_touserdata(L, lua_upvalueindex(1)));
        
        LUACG_REPEAT(n, _, repeat_f)
        R r = (*pHandler->mFunc)(LUACG_ENUM_PARAMS(n, a));
        LuaPush(L, r);
        return 1;
    }
};

template<LUACG_ENUM_PARAMS(n, typename A)>
class TableMethod<void (*)(LUACG_ENUM_PARAMS(n, A))>
{
    typedef void (*Type)(LUACG_ENUM_PARAMS(n, A));
    Type mFunc;
public:

    explicit TableMethod(Type pFunc) : mFunc(pFunc)
    {
    }

    static int create(lua_State* L, Type pTableFunc)
    {
        TableMethod* pHandler = new TableMethod(pTableFunc);

        lua_pushlightuserdata(L, pHandler);
        lua_pushcclosure(L, index, 1);
        return 1;
    }

    static int index(lua_State* L)
    {
        TableMethod* pHandler = static_cast<TableMethod*>(lua_touserdata(L, lua_upvalueindex(1)));

        LUACG_REPEAT(n, _, repeat_f)
        (*pHandler->mFunc)(LUACG_ENUM_PARAMS(n, a));
        return 0;
    }
};

#endif // LUACG_IS_ITERATING
