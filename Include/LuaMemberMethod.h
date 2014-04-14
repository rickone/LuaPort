#ifndef LUACG_IS_ITERATING

/*
__index = function(tb)
    up1 -> tb
    return function(p1, p2, ...)
        X* pObj = LuaClassCastorManager::sharedClassCastorManager()->castType(tb.__obj, tb.__class, "X");
        if pObj then
            pObj->*XXX(p1, p2, ...);
        end
    end;
end,
*/

LUA_PORT_NAMESPACE_BEGIN

template<typename T>
class MemberMethod;

#define n LUACG_ITERATOR()
#define repeat_f(_, n) LUACG_CAT(A, n) LUACG_CAT(a, n) = LuaTo<LUACG_CAT(A, n)>(L, LUACG_INC(n));

#define LUACG_ITERATOR_BEGIN    0
#define LUACG_ITERATOR_END      LUA_PORT_FUNC_PARAM_LIMITS
#define LUACG_ITERATE_FILE      "LuaMemberMethod.h"
#include LUACG_ITERATE()

#undef repeat_f
#undef n

template<typename B>
class MemberMethod<int (B::*)(lua_State*)>
{
    typedef int (B::*Type)(lua_State*);
    Type mMemberFunc;
public:

    explicit MemberMethod(Type pMemberFunc) : mMemberFunc(pMemberFunc)
    {
    }

    static int create(lua_State* L, Type pMemberFunc)
    {
        MemberMethod* pHandler = new MemberMethod(pMemberFunc);
        lua_pushlightuserdata(L, pHandler);
        lua_pushcclosure(L, index, 1);
        return 1;
    }

    static int index(lua_State* L)
    {
        lua_pushvalue(L, lua_upvalueindex(1));
        lua_pushcclosure(L, indexClosure, 2);
        return 1;
    }

    static int indexClosure(lua_State* L)
    {
        int nTableIndex = lua_upvalueindex(1);
        MemberMethod* pHandler = static_cast<MemberMethod*>(lua_touserdata(L, lua_upvalueindex(2)));
        const char* pszBaseClassName = ClassExport<B>::getClassName();

        lua_pushstring(L, MT_OBJECT);
        lua_rawget(L, nTableIndex);

        void* pvObj = lua_touserdata(L, -1);
        lua_pop(L, 1);

        lua_pushstring(L, MT_CLASS);
        lua_rawget(L, nTableIndex);

        const char* pszClassName = lua_tostring(L, -1);
        lua_pop(L, 1);

        pvObj = Castor::sharedLuaCastor()->castType(pvObj, pszClassName, pszBaseClassName);
        if (!pvObj)
            return 0;

        return (static_cast<B*>(pvObj)->*(pHandler->mMemberFunc))(L);
    }
};

LUA_PORT_NAMESPACE_END

#else // LUACG_IS_ITERATING

template<typename B, typename R LUACG_COMMA_IF(n) LUACG_ENUM_PARAMS(n, typename A)>
class MemberMethod<R (B::*)(LUACG_ENUM_PARAMS(n, A))>
{
    typedef R (B::*Type)(LUACG_ENUM_PARAMS(n, A));
    Type mMemberFunc;
public:

    explicit MemberMethod(Type pMemberFunc) : mMemberFunc(pMemberFunc)
    {
    }

    static int create(lua_State* L, Type pMemberFunc)
    {
        MemberMethod* pHandler = new MemberMethod(pMemberFunc);
        lua_pushlightuserdata(L, pHandler);
        lua_pushcclosure(L, index, 1);
        return 1;
    }

    static int index(lua_State* L)
    {
        lua_pushvalue(L, lua_upvalueindex(1));
        lua_pushcclosure(L, indexClosure, 2);
        return 1;
    }

    static int indexClosure(lua_State* L)
    {
        int nTableIndex = lua_upvalueindex(1);
        MemberMethod* pHandler = static_cast<MemberMethod*>(lua_touserdata(L, lua_upvalueindex(2)));
        const char* pszBaseClassName = ClassExport<B>::getClassName();
        
        lua_pushstring(L, MT_OBJECT);
        lua_rawget(L, nTableIndex);

        void* pvObj = lua_touserdata(L, -1);
        lua_pop(L, 1);

        lua_pushstring(L, MT_CLASS);
        lua_rawget(L, nTableIndex);

        const char* pszClassName = lua_tostring(L, -1);
        lua_pop(L, 1);

        pvObj = Castor::sharedLuaCastor()->castType(pvObj, pszClassName, pszBaseClassName);
        if (!pvObj)
            return 0;

        LUACG_REPEAT(n, _, repeat_f)
        R r = (static_cast<B*>(pvObj)->*(pHandler->mMemberFunc))(LUACG_ENUM_PARAMS(n, a));
        LuaPush(L, r);
        return 1;
    }
};

template<typename B LUACG_COMMA_IF(n) LUACG_ENUM_PARAMS(n, typename A)>
class MemberMethod<void (B::*)(LUACG_ENUM_PARAMS(n, A))>
{
    typedef void (B::*Type)(LUACG_ENUM_PARAMS(n, A));
    Type mMemberFunc;
public:

    explicit MemberMethod(Type pMemberFunc) : mMemberFunc(pMemberFunc)
    {
    }

    static int create(lua_State* L, Type pMemberFunc)
    {
        MemberMethod* pHandler = new MemberMethod(pMemberFunc);
        lua_pushlightuserdata(L, pHandler);
        lua_pushcclosure(L, index, 1);
        return 1;
    }

    static int index(lua_State* L)
    {
        lua_pushvalue(L, lua_upvalueindex(1));
        lua_pushcclosure(L, indexClosure, 2);
        return 1;
    }

    static int indexClosure(lua_State* L)
    {
        int nTableIndex = lua_upvalueindex(1);
        MemberMethod* pHandler = static_cast<MemberMethod*>(lua_touserdata(L, lua_upvalueindex(2)));
        const char* pszBaseClassName = ClassExport<B>::getClassName();

        lua_pushstring(L, MT_OBJECT);
        lua_rawget(L, nTableIndex);

        void* pvObj = lua_touserdata(L, -1);
        lua_pop(L, 1);

        lua_pushstring(L, MT_CLASS);
        lua_rawget(L, nTableIndex);

        const char* pszClassName = lua_tostring(L, -1);
        lua_pop(L, 1);

        pvObj = Castor::sharedLuaCastor()->castType(pvObj, pszClassName, pszBaseClassName);
        if (!pvObj)
            return 0;

        LUACG_REPEAT(n, _, repeat_f)
        (static_cast<B*>(pvObj)->*(pHandler->mMemberFunc))(LUACG_ENUM_PARAMS(n, a));
        return 0;
    }
};

#endif // LUACG_IS_ITERATING
