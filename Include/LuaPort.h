/* LuaPort by 2013/4/7 Rick(rickone@sina.com) */
#pragma once

#define LUA_PORT_NAMESPACE_BEGIN namespace LuaPort {
#define LUA_PORT_NAMESPACE_END }

#ifndef LUA_PORT_TRACE
#define LUA_PORT_TRACE printf
#endif

// C-Functions' params must equal or less than LUA_EX_FUNC_PARAM_LIMITS, which can be [0, 32)
#define LUA_PORT_FUNC_PARAM_LIMITS 30
#if !(LUA_PORT_FUNC_PARAM_LIMITS >= 0) || !(LUA_PORT_FUNC_PARAM_LIMITS < 32)
#error LUA_PORT_FUNC_PARAM_LIMITS must be equal or greater than 0 and less than 32
#endif

// LuaCall accept params must equal or less than LUA_EX_CALL_PARAM_LIMITS, which can be [0, 32)
#define LUA_PORT_CALL_PARAM_LIMITS 30
#if !(LUA_PORT_CALL_PARAM_LIMITS >= 0) || !(LUA_PORT_CALL_PARAM_LIMITS < 32)
#error LUA_PORT_CALL_PARAM_LIMITS must be equal or greater than 0 and less than 32
#endif

// LuaResult accept params must equal or less than LUA_EX_RESULT_PARAM_LIMITS, which can be [0, 32)
#define LUA_PORT_RESULT_PARAM_LIMITS 30
#if !(LUA_PORT_RESULT_PARAM_LIMITS >= 0) || !(LUA_PORT_RESULT_PARAM_LIMITS < 32)
#error LUA_PORT_RESULT_PARAM_LIMITS must be equal or greater than 0 and less than 32
#endif

#include <list>
#include <cassert>
#include <string>
#include <string.h>
#include "LuaBridge.h"
#include "LuaCodeGenerator.h"
#include "LuaClassExport.h"
#include "LuaCastor.h"
#include "LuaMetaTable.h"
#include "LuaMemberMethod.h"
#include "LuaMemberProperty.h"
#include "LuaCustomMethodProperty.h"
#include "LuaTableMethod.h"

#define LUA_PORT_CLASS(Class) template<> const char* LuaPort::ClassExport<Class>::s_pszClassName = #Class

#define LUA_PORT_EXPORT_CREATE(L, Class) LuaPort::ClassExport<Class>::create(L)

#define LUA_PORT_EXPORT_METHOD(L, Class, Method) LuaPort::ClassExport<Class>::addMemberMethod(L, #Method, &Class::Method)
#define LUA_PORT_EXPORT_PROPERTY(L, Class, Property) LuaPort::ClassExport<Class>::addMemberProperty(L, #Property, &Class::Property)
#define LUA_PORT_EXPORT_PROPERTY_R(L, Class, Property) LuaPort::ClassExport<Class>::addMemberProperty(L, #Property, &Class::Property, true)

#define LUA_PORT_INHERIT(L, DerivedClass, BaseClass) \
    do \
    { \
        LuaPort::inheritAllMemberMethod(L, #DerivedClass, #BaseClass); \
        LuaPort::Castor::sharedLuaCastor()->registerCastor(#DerivedClass, #BaseClass, &LuaPort::TemplateCastor<DerivedClass, BaseClass>::StaticCastor); \
        LuaPort::Castor::sharedLuaCastor()->registerCastor(#BaseClass, #DerivedClass, &LuaPort::TemplateCastor<DerivedClass, BaseClass>::DynamicCastor); \
    } while (false)
