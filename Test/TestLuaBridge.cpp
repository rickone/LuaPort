#include "stdafx.h"
#include <string.h>
#include <limits.h>
#include <functional>

namespace std
{
    template<>
    struct not_equal_to<const char*>
        : public binary_function<const char*, const char*, bool>
    {
        bool operator()(const char* _Left, const char* _Right) const
        {
            return strcmp(_Left, _Right) != 0;
        }
    };

    template<>
    struct not_equal_to<char*>
        : public binary_function<char*, char*, bool>
    {
        bool operator()(char* _Left, char* _Right) const
        {
            return strcmp(_Left, _Right) != 0;
        }
    };
} // namespace std

#define TEST_BRIDGE(Type, Value) \
    do \
    { \
        int nTop = lua_gettop(L); \
        LuaPort::LuaPush(L, Value); \
        Type ret = LuaPort::LuaTo<Type>(L, -1); \
        if (std::not_equal_to<Type>()(ret, Value)) \
        { \
            nResult = false; \
            printf("Test Switch Type '%s' failed!\n", #Type); \
        } \
        lua_settop(L, nTop); \
    } while (false)

int TestLuaBridge(lua_State* L)
{
    int nResult = true;

    TEST_BRIDGE(bool, false);
    TEST_BRIDGE(bool, true);
    TEST_BRIDGE(char, SCHAR_MIN);
    TEST_BRIDGE(char, 0);
    TEST_BRIDGE(char, SCHAR_MAX);
    TEST_BRIDGE(unsigned char, 0);
    TEST_BRIDGE(unsigned char, UCHAR_MAX);
    TEST_BRIDGE(short, SHRT_MIN);
    TEST_BRIDGE(short, 0);
    TEST_BRIDGE(short, SHRT_MAX);
    TEST_BRIDGE(unsigned short, 0);
    TEST_BRIDGE(unsigned short, USHRT_MAX);
    TEST_BRIDGE(int, INT_MIN);
    TEST_BRIDGE(int, 0);
    TEST_BRIDGE(int, INT_MAX);
    TEST_BRIDGE(unsigned int, 0);
    TEST_BRIDGE(unsigned int, UINT_MAX);
    TEST_BRIDGE(long, LONG_MIN);
    TEST_BRIDGE(long, 0);
    TEST_BRIDGE(long, LONG_MAX);
    TEST_BRIDGE(unsigned long, 0);
    TEST_BRIDGE(unsigned long, ULONG_MAX);
    TEST_BRIDGE(const char*, "");
    TEST_BRIDGE(const char*, "LuaPort");
    TEST_BRIDGE(char*, "");
    TEST_BRIDGE(char*, "Script");
    TEST_BRIDGE(float, -100.0f);
    TEST_BRIDGE(float, 0.0f);
    TEST_BRIDGE(float, 100.0f);
    TEST_BRIDGE(double, -100.0);
    TEST_BRIDGE(double, 0.0);
    TEST_BRIDGE(double, 100.0);

    return nResult;
}
