#pragma once

LUA_PORT_NAMESPACE_BEGIN

#define MT_MEMBERS     "members"
#define MT_INDEX       "__index"
#define MT_NEWINDEX    "__newindex"
#define MT_OBJECT      "__object"
#define MT_CLASS       "__class"

int createMetaTable(lua_State* L, const char* pszClass);
int getMetaTable(lua_State* L, const char* pszClass);
int inheritMemberMethod(lua_State* L, const char* pszClassSrc, const char* pszClassDst, const char* pszMemberDst);
int inheritAllMemberMethod(lua_State* L, const char* pszClassSrc, const char* pszClassDst);
int addMemberIndexMethod(lua_State* L, int nFuncIdx, const char* pszClass, const char* pszMember);
int addMemberNewIndexMethod(lua_State* L, int nFuncIdx, const char* pszClass, const char* pszMember);
int pushObjectImpl(lua_State* L, void* pvObj, const char* pszClass);
int dumpMetaTable(lua_State* L, int nDelpth = 0);

LUA_PORT_NAMESPACE_END
