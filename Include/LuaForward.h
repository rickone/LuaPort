#if !defined(LUACG_ITERATOR_BEGIN) || !defined(LUACG_ITERATOR_END) || !defined(LUACG_ITERATE_FILE)
#error Undefined LUACG_ITERATE_LIMIT or LUACG_ITERATE_FILE!
#endif
#
#if LUACG_ITERATOR_BEGIN < 0
#error LUACG_ITERATOR_BEGIN must be equal or greater than 0
#endif
#
#if LUACG_ITERATOR_END > 31
#error LUACG_ITERATOR_END must be less than 32
#endif
#
#if defined(LUACG_ITERATOR)
#error Redefined LUACG_ITERATOR
#endif
#
#define LUACG_IS_ITERATING
#
#define LUACG_ITERATOR() LUACG_ITERATOR_0
#include "LuaIterateFile.h"
#define LUACG_ITERATOR() LUACG_ITERATOR_1
#include "LuaIterateFile.h"
#define LUACG_ITERATOR() LUACG_ITERATOR_2
#include "LuaIterateFile.h"
#define LUACG_ITERATOR() LUACG_ITERATOR_3
#include "LuaIterateFile.h"
#define LUACG_ITERATOR() LUACG_ITERATOR_4
#include "LuaIterateFile.h"
#define LUACG_ITERATOR() LUACG_ITERATOR_5
#include "LuaIterateFile.h"
#define LUACG_ITERATOR() LUACG_ITERATOR_6
#include "LuaIterateFile.h"
#define LUACG_ITERATOR() LUACG_ITERATOR_7
#include "LuaIterateFile.h"
#define LUACG_ITERATOR() LUACG_ITERATOR_8
#include "LuaIterateFile.h"
#define LUACG_ITERATOR() LUACG_ITERATOR_9
#include "LuaIterateFile.h"
#define LUACG_ITERATOR() LUACG_ITERATOR_10
#include "LuaIterateFile.h"
#define LUACG_ITERATOR() LUACG_ITERATOR_11
#include "LuaIterateFile.h"
#define LUACG_ITERATOR() LUACG_ITERATOR_12
#include "LuaIterateFile.h"
#define LUACG_ITERATOR() LUACG_ITERATOR_13
#include "LuaIterateFile.h"
#define LUACG_ITERATOR() LUACG_ITERATOR_14
#include "LuaIterateFile.h"
#define LUACG_ITERATOR() LUACG_ITERATOR_15
#include "LuaIterateFile.h"
#define LUACG_ITERATOR() LUACG_ITERATOR_16
#include "LuaIterateFile.h"
#define LUACG_ITERATOR() LUACG_ITERATOR_17
#include "LuaIterateFile.h"
#define LUACG_ITERATOR() LUACG_ITERATOR_18
#include "LuaIterateFile.h"
#define LUACG_ITERATOR() LUACG_ITERATOR_19
#include "LuaIterateFile.h"
#define LUACG_ITERATOR() LUACG_ITERATOR_20
#include "LuaIterateFile.h"
#define LUACG_ITERATOR() LUACG_ITERATOR_21
#include "LuaIterateFile.h"
#define LUACG_ITERATOR() LUACG_ITERATOR_22
#include "LuaIterateFile.h"
#define LUACG_ITERATOR() LUACG_ITERATOR_23
#include "LuaIterateFile.h"
#define LUACG_ITERATOR() LUACG_ITERATOR_24
#include "LuaIterateFile.h"
#define LUACG_ITERATOR() LUACG_ITERATOR_25
#include "LuaIterateFile.h"
#define LUACG_ITERATOR() LUACG_ITERATOR_26
#include "LuaIterateFile.h"
#define LUACG_ITERATOR() LUACG_ITERATOR_27
#include "LuaIterateFile.h"
#define LUACG_ITERATOR() LUACG_ITERATOR_28
#include "LuaIterateFile.h"
#define LUACG_ITERATOR() LUACG_ITERATOR_29
#include "LuaIterateFile.h"
#define LUACG_ITERATOR() LUACG_ITERATOR_30
#include "LuaIterateFile.h"
#define LUACG_ITERATOR() LUACG_ITERATOR_31
#include "LuaIterateFile.h"
#
#undef LUACG_IS_ITERATING
#
#undef LUACG_ITERATOR_BEGIN
#undef LUACG_ITERATOR_END
#undef LUACG_ITERATE_FILE
