#pragma once

LUA_PORT_NAMESPACE_BEGIN

template<typename T>
class MemberMethod;

template<typename T>
class MemberProperty;

template<typename C>
class ClassExport
{
public:
    static const char* s_pszClassName;

    static const char* getClassName() { return s_pszClassName; }

    static void create(lua_State* L)
    {
        int nTop = lua_gettop(L);
        getMetaTable(L, getClassName());
        if (!lua_istable(L, -1))
            createMetaTable(L, getClassName());
        lua_settop(L, nTop);
    }

    template<typename T>
    static void addMemberMethod(lua_State* L, const char* pszMember, T t)
    {
        int nTop = lua_gettop(L);
        MemberMethod<T>::create(L, t);
        addMemberIndexMethod(L, -1, getClassName(), pszMember);
        lua_settop(L, nTop);
    }

    template<typename T>
    static void addMemberProperty(lua_State* L, const char* pszMember, T t, bool bReadOnly = false)
    {
        int nTop = lua_gettop(L);
        MemberProperty<T>::create(L, t);
        addMemberIndexMethod(L, -2, getClassName(), pszMember);

        if (!bReadOnly)
        {
            addMemberNewIndexMethod(L, -1, getClassName(), pszMember);
        }
        lua_settop(L, nTop);
    }
};

template<typename T>
static int pushObject(lua_State* L, T* t)
{
    return pushObjectImpl(L, t, ClassExport<T>::getClassName());
}

LUA_PORT_NAMESPACE_END
