/*
 * Lua compatibility shims
 * Provides macros for cross-version Lua compatibility (5.1/JIT through 5.4)
 */
#ifndef LUAST_LUA_COMPAT_H
#define LUAST_LUA_COMPAT_H

#include <lua.h>
#include <lauxlib.h>

/*
 * luaL_checkint/luaL_optint: existed in 5.1/5.2, removed in 5.3+
 * luaL_checkunsigned/luaL_optunsigned/lua_pushunsigned: added in 5.2, removed in 5.3+
 *
 * For LuaJIT (5.1-based): need to define the unsigned variants
 * For Lua 5.3+: need to define all of them
 */

/* Lua 5.1 and LuaJIT don't have the unsigned functions */
#if LUA_VERSION_NUM < 502

#ifndef lua_pushunsigned
#define lua_pushunsigned(L, n) lua_pushinteger(L, (lua_Integer)(n))
#endif

#ifndef luaL_checkunsigned
#define luaL_checkunsigned(L, n)   ((unsigned long)luaL_checkinteger(L, n))
#endif

#ifndef luaL_optunsigned
#define luaL_optunsigned(L, n, d)  ((unsigned long)luaL_optinteger(L, n, (lua_Integer)(d)))
#endif

#endif /* LUA_VERSION_NUM < 502 */

/* Lua 5.3+ removed checkint/optint and the unsigned functions */
#if LUA_VERSION_NUM >= 503

#ifndef luaL_checkint
#define luaL_checkint(L, n)    ((int)luaL_checkinteger(L, n))
#endif

#ifndef luaL_optint
#define luaL_optint(L, n, d)   ((int)luaL_optinteger(L, n, d))
#endif

#ifndef luaL_checklong
#define luaL_checklong(L, n)   ((long)luaL_checkinteger(L, n))
#endif

#ifndef luaL_optlong
#define luaL_optlong(L, n, d)  ((long)luaL_optinteger(L, n, d))
#endif

#ifndef lua_pushunsigned
#define lua_pushunsigned(L, n) lua_pushinteger(L, (lua_Integer)(n))
#endif

#ifndef luaL_checkunsigned
#define luaL_checkunsigned(L, n)   ((lua_Unsigned)luaL_checkinteger(L, n))
#endif

#ifndef luaL_optunsigned
#define luaL_optunsigned(L, n, d)  ((lua_Unsigned)luaL_optinteger(L, n, (lua_Integer)(d)))
#endif

#endif /* LUA_VERSION_NUM >= 503 */

#endif /* LUAST_LUA_COMPAT_H */
