#include "stdafx.h"
#include "LuaMetaTable.h"

LUA_PORT_NAMESPACE_BEGIN

int indexMetaTable(lua_State* L)
/*
function(t, k)
    local f = up1.members[k];
    if f and f.index then
        return f.index(t);
    end
    return nil;
end,
*/
{
    int nMetaTableIndex = lua_upvalueindex(1); // t, k

    lua_pushstring(L, MT_MEMBERS);
    lua_rawget(L, nMetaTableIndex); // t, k, members

    lua_pushvalue(L, 2); // t, k, members, k
    lua_rawget(L, -2); // t, k, members, f

    if (lua_istable(L, -1))
    {
        lua_pushstring(L, MT_INDEX);
        lua_rawget(L, -2); // t, k, members, f, index

        if (lua_isfunction(L, -1))
        {
            lua_pushvalue(L, 1); // t, k, members, f, index, t
            lua_pcall(L, 1, 1, 0); // t, k, members, f, result
            return 1;
        }
    }

    lua_pushnil(L);
    return 1;
}

int newindexMetaTable(lua_State* L)
/*
function(t, k, v)
    local f = up1.members[k];
    if f and f.newindex then
        f.newindex(t, v);
        return true;
    end
    return false;
end,
*/
{
    int nMetaTableIndex = lua_upvalueindex(1); // t, k, v

    lua_pushstring(L, MT_MEMBERS);
    lua_rawget(L, nMetaTableIndex); // t, k, v, members

    lua_pushvalue(L, 2); // t, k, v, members, k
    lua_rawget(L, -2); // t, k, v, members, f

    if (lua_istable(L, -1))
    {
        lua_pushstring(L, MT_NEWINDEX);
        lua_rawget(L, -2); // t, k, v, members, f, newindex

        if (lua_isfunction(L, -1))
        {
            lua_pushvalue(L, 1); // t, k, v, members, f, newindex, t
            lua_pushvalue(L, 3); // t, k, v, members, f, newindex, t, v
            lua_pcall(L, 2, 0, 0); // t, k, v, members, f

            lua_pushboolean(L, true);
            return 1;
        }
    }

    lua_pushboolean(L, false);
    return 1;
}

int createMetaTable(lua_State* L, const char* pszClass)
{
    luaL_newmetatable(L, pszClass);

    lua_pushvalue(L, -1);
    lua_pushcclosure(L, indexMetaTable, 1);
    lua_setfield(L, -2, MT_INDEX);

    lua_pushvalue(L, -1);
    lua_pushcclosure(L, newindexMetaTable, 1);
    lua_setfield(L, -2, MT_NEWINDEX);

    lua_newtable(L);
    lua_setfield(L, -2, MT_MEMBERS);

    return 1;
}

int getMetaTable(lua_State* L, const char* pszClass)
{
    luaL_getmetatable(L, pszClass);
    return 1;
}

int inheritMemberMethod(lua_State* L, const char* pszClassSrc, const char* pszClassDst, const char* pszMemberDst)
{
    int nTop = lua_gettop(L);

    luaL_getmetatable(L, pszClassSrc);

    lua_pushstring(L, MT_MEMBERS);
    lua_rawget(L, -2);

    int nSrcMembersIndex = lua_gettop(L);

    luaL_getmetatable(L, pszClassDst);

    lua_pushstring(L, MT_MEMBERS);
    lua_rawget(L, -2);

    lua_pushstring(L, pszMemberDst);
    lua_rawget(L, -2);

    if (lua_istable(L, -1))
    {
        lua_pushstring(L, pszMemberDst);
        lua_pushvalue(L, -2);
        lua_rawset(L, nSrcMembersIndex);
    }

    lua_settop(L, nTop);
    return 0;
}

int inheritAllMemberMethod(lua_State* L, const char* pszClassSrc, const char* pszClassDst)
{
    int nTop = lua_gettop(L);

    luaL_getmetatable(L, pszClassSrc);

    lua_pushstring(L, MT_MEMBERS);
    lua_rawget(L, -2);

    int nSrcMembersIndex = lua_gettop(L);

    luaL_getmetatable(L, pszClassDst);

    lua_pushstring(L, MT_MEMBERS);
    lua_rawget(L, -2);

    lua_pushnil(L);
    while (lua_next(L, -2))
    {
        lua_pushvalue(L, -2);
        lua_pushvalue(L, -2);
        lua_rawset(L, nSrcMembersIndex);

        lua_pop(L, 1);
    }

    lua_settop(L, nTop);
    return 0;
}

void createMemberTable(lua_State* L, const char* pszClass, const char* pszMember)
{
    luaL_getmetatable(L, pszClass); // mt

    lua_pushstring(L, MT_MEMBERS);
    lua_rawget(L, -2); // mt, members

    lua_pushstring(L, pszMember);
    lua_rawget(L, -2); // mt, members, members.pszMember

    if (!lua_istable(L, -1))
    {
        lua_pop(L, 1); // mt, members
        lua_newtable(L); // mt, members, {}

        lua_pushstring(L, pszMember); // mt, members, {}, pszMember
        lua_pushvalue(L, -2); // mt, members, {}, pszMember, {}
        lua_rawset(L, -4); // mt, members, {}
    }
}

int addMemberIndexMethod(lua_State* L, int nFuncIdx, const char* pszClass, const char* pszMember)
{
    int nTop = lua_gettop(L);
    if (nFuncIdx < 0)
        nFuncIdx = nTop + nFuncIdx + 1;

    createMemberTable(L, pszClass, pszMember);

    lua_pushstring(L, MT_INDEX);
    lua_pushvalue(L, nFuncIdx);
    lua_rawset(L, -3);

    lua_settop(L, nTop);
    return 0;
}

int addMemberNewIndexMethod(lua_State* L, int nFuncIdx, const char* pszClass, const char* pszMember)
{
    int nTop = lua_gettop(L);
    if (nFuncIdx < 0)
        nFuncIdx = nTop + nFuncIdx + 1;

    createMemberTable(L, pszClass, pszMember);

    lua_pushstring(L, MT_NEWINDEX);
    lua_pushvalue(L, nFuncIdx);
    lua_rawset(L, -3);

    lua_settop(L, nTop);
    return 0;
}

int pushObjectImpl(lua_State* L, void* pvObj, const char* pszClass)
{
    lua_newtable(L);

    lua_pushstring(L, MT_OBJECT);
    lua_pushlightuserdata(L, pvObj);
    lua_rawset(L, -3);

    lua_pushstring(L, MT_CLASS);
    lua_pushstring(L, pszClass);
    lua_rawset(L, -3);

    luaL_getmetatable(L, pszClass);
    lua_setmetatable(L, -2);

    return 1;
}

int dumpMetaTable(lua_State* L, int nDelpth)
{
    lua_pushnil(L);
    while (lua_next(L, -2))
    {
        int nKeyType = lua_type(L, -2);
        int nValueType = lua_type(L, -1);

        for (int i = 0; i < nDelpth; i++)
        {
            printf("\t");
        }
        switch (nKeyType)
        {
        case LUA_TSTRING:
            printf("[%s]=", lua_tostring(L, -2));
            break;
        case LUA_TNUMBER:
            printf("[%f]=", lua_tonumber(L, -1));
            break;

        case LUA_TTABLE:
            printf("[{\n");
            lua_pushvalue(L, -2);
            dumpMetaTable(L, nDelpth + 1);
            lua_pop(L, 1);
            printf("}]=");
            break;


        default:
            break;
        }

        switch (nValueType)
        {
        case LUA_TSTRING:
            printf("%s\n", lua_tostring(L, -1));
            break;

        case LUA_TNUMBER:
            printf("%f\n", lua_tostring(L, -1));
            break;

        case LUA_TFUNCTION:
            printf("FUNCTION\n");
            break;

        case LUA_TTABLE:
            printf("{\n");
            dumpMetaTable(L, nDelpth + 1);
            printf("}\n");
            break;

        default:
            break;
        }

        lua_pop(L, 1);
    }

    return 0;
}

LUA_PORT_NAMESPACE_END
