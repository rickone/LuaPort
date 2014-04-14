#pragma once

LUA_PORT_NAMESPACE_BEGIN

template<typename T>
struct Bridge;

template<typename T>
inline T LuaTo(lua_State* L, int idx)
{
    return Bridge<T>::To(L, idx);
}

template<typename T>
inline void LuaPush(lua_State* L, T value)
{
    Bridge<T>::Push(L, value);
}

LUA_PORT_NAMESPACE_END

#define LUA_BRIDGE_DEFINE(c_type, err_code, check_func, to_func, push_func) \
    namespace LuaPort { \
        template<> \
        struct Bridge<c_type> \
        { \
            static c_type To(lua_State* L, int idx) \
            { \
                if (!check_func(L, idx)) \
                { \
                    LUA_PORT_TRACE("[LuaPort] Bridge::To failed from LUA! C-type '%s'\n", #c_type); \
                    return err_code; \
                } \
                return (c_type)to_func(L, idx); \
            } \
            static void Push(lua_State* L, c_type value) \
            { \
                push_func(L, value); \
            } \
        }; \
    }

#define LUA_PORT_TO_BOOLEAN(L, idx) (lua_toboolean(L, idx) != 0)
#define LUA_PORT_TO_CHAR_STAR(L, idx) const_cast<char*>(lua_tostring(L, idx)) // dangerious
#define LUA_PORT_ASSERT_FUNC(L, idx) (assert(false), false)
#define LUA_PORT_NULL_FUNC(L, idx) NULL

LUA_BRIDGE_DEFINE(bool, false, lua_isboolean, LUA_PORT_TO_BOOLEAN, lua_pushboolean);
LUA_BRIDGE_DEFINE(char, 0, lua_isnumber, lua_tointeger, lua_pushinteger);
LUA_BRIDGE_DEFINE(unsigned char, 0, lua_isnumber, lua_tounsigned, lua_pushunsigned);
LUA_BRIDGE_DEFINE(short, 0, lua_isnumber, lua_tointeger, lua_pushinteger);
LUA_BRIDGE_DEFINE(unsigned short, 0, lua_isnumber, lua_tounsigned, lua_pushunsigned);
LUA_BRIDGE_DEFINE(int, 0, lua_isnumber, lua_tointeger, lua_pushinteger);
LUA_BRIDGE_DEFINE(unsigned int, 0, lua_isnumber, lua_tounsigned, lua_pushunsigned);

// 在64位下某些系统long是64位，64位整形转double是不能保证精度的
LUA_BRIDGE_DEFINE(long, 0, lua_isnumber, lua_tointeger, lua_pushinteger);
LUA_BRIDGE_DEFINE(unsigned long, 0, lua_isnumber, lua_tounsigned, lua_pushunsigned);

LUA_BRIDGE_DEFINE(const char*, NULL,lua_isstring, lua_tostring, lua_pushstring);
LUA_BRIDGE_DEFINE(char*, NULL, lua_isstring, LUA_PORT_TO_CHAR_STAR, lua_pushstring);
//LUA_BRIDGE_DEFINE(const wchar_t*, NULL, LUA_PORT_ASSERT_FUNC, LUA_PORT_NULL_FUNC, LUA_PORT_NULL_FUNC);
//LUA_BRIDGE_DEFINE(wchar_t*, NULL, LUA_PORT_ASSERT_FUNC, LUA_PORT_NULL_FUNC, LUA_PORT_NULL_FUNC);
LUA_BRIDGE_DEFINE(float, 0.0f, lua_isnumber, lua_tonumber, lua_pushnumber);
LUA_BRIDGE_DEFINE(double, 0.0, lua_isnumber, lua_tonumber, lua_pushnumber);
