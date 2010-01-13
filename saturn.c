#include <lua5.1/lua.h>
#include <lua5.1/lauxlib.h>
#include <lua5.1/lualib.h>

static int average(lua_State *L) {
    int n = lua_gettop(L);
    double sum = 0;
    int i;

    for (i = 1; i <= n; ++i) {
        sum += lua_tonumber(L, i);
    }

    lua_pushnumber(L, sum / n);

    return 1;
}

static int fac(int n) {
    return n <= 1 ? 1 : n * fac(n - 1);
}

static int factorial(lua_State *L) {
    int n = lua_tonumber(L, -1);
    printf("%d\n", n);
    
    int result = fac(n);
    
    lua_pushnumber(L, result);

    return 1;
}

static const luaL_reg saturn[] = {
    {"average", average},
    {"factorial", factorial},
    {NULL, NULL}
};

LUALIB_API int luaopen_saturn(lua_State *L) {
    luaL_openlib(L, "saturn", saturn, 0);
    return 1;
}

