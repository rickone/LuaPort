#pragma once

/*
"property" = {
__index = function(tb)
    if tb.__class == "X" then
        return tb.__obj -> some_property;
    end
    return nil;
end,
__newindex = function(tb, v)
    if tb.__class == "X" then
        tb.__obj -> some_property = v;
    end
end}
*/

LUA_PORT_NAMESPACE_BEGIN

template<typename T>
class MemberProperty;

template<typename B, typename T>
class MemberProperty<T (B::*)>
{
    typedef T(B::*Type);
    Type mMemberProperty;
public:

    explicit MemberProperty(Type pMemberProperty) : mMemberProperty(pMemberProperty)
    {
    }

    static int create(lua_State* L, Type pMemberFunc)
    {
        MemberProperty* pHandler = new MemberProperty(pMemberFunc);
        lua_pushlightuserdata(L, pHandler);
        lua_pushcclosure(L, index, 1);

        lua_pushlightuserdata(L, pHandler);
        lua_pushcclosure(L, newIndex, 1);
        return 2;
    }

    static int index(lua_State* L)
    {
        MemberProperty* pHandler = (MemberProperty*)lua_touserdata(L, lua_upvalueindex(1));
        const char* pszBaseClassName = ClassExport<B>::getClassName();
        
        lua_pushstring(L, MT_OBJECT);
        lua_rawget(L, 1);

        void* pvObj = lua_touserdata(L, -1);
        lua_pop(L, 1);

        lua_pushstring(L, MT_CLASS);
        lua_rawget(L, 1);

        const char* pszClassName = lua_tostring(L, -1);
        lua_pop(L, 1);

        pvObj = Castor::sharedLuaCastor()->castType(pvObj, pszClassName, pszBaseClassName);
        if (!pvObj)
            return 0;

        T t = static_cast<B*>(pvObj)->*(pHandler->mMemberProperty);
        LuaPort::Bridge<T>::Push(L, t);
        return 1;
    }

    static int newIndex(lua_State* L)
    {
        MemberProperty* pHandler = (MemberProperty*)lua_touserdata(L, lua_upvalueindex(1));
        const char* pszBaseClassName = ClassExport<B>::getClassName();

        lua_pushstring(L, MT_OBJECT);
        lua_rawget(L, 1);

        void* pvObj = lua_touserdata(L, -1);
        lua_pop(L, 1);

        lua_pushstring(L, MT_CLASS);
        lua_rawget(L, 1);

        const char* pszClassName = lua_tostring(L, -1);
        lua_pop(L, 1);

        pvObj = Castor::sharedLuaCastor()->castType(pvObj, pszClassName, pszBaseClassName);
        if (!pvObj)
            return 0;

        T t = LuaPort::Bridge<T>::To(L, 2);
        static_cast<B*>(pvObj)->*(pHandler->mMemberProperty) = t;
        return 0;
    }
};

LUA_PORT_NAMESPACE_END
