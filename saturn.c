#include <lua5.1/lua.h>
#include <lua5.1/lauxlib.h>
#include <lua5.1/lualib.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int v;
    struct Node *next;
};

struct List {
    struct Node *head;
};

static struct List *list;

static int new(lua_State *L) {
    list = malloc(sizeof(struct List));

    return 0;
}

static int prepend(lua_State *L) {
    if (!list) {
        fprintf(stderr, "You should first call new()\n");
        return 0;
    }
    int v = lua_tonumber(L , -1);
    struct Node node = malloc(sizeof(struct Node));
    node->v = v;
    if (!list->head) {
        list->head = node;
    } else {
        node->next = list->head;
        list->head = node;
    }

    return 1;
}

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

    int result = fac(n);
    
    lua_pushnumber(L, result);

    return 1;
}

static int getstring(lua_State *L) {
    char buff[256];

    puts("Enter a word: ");
    if (scanf("%s", buff) != 1)
        fprintf(stderr, "Something went horribly wrong!");
    
    lua_pushstring(L, buff);

    return 1;
}

static int n = 0;

static int increment(lua_State *L) {
    lua_pushnumber(L, ++n);

    return 1;
}

static const luaL_reg saturn[] = {
    {"average", average},
    {"factorial", factorial},
    {"getstring", getstring},
    {"increment", increment},
    {"new", new},
    {"prepend", prepend},
    {NULL, NULL}
};

LUALIB_API int luaopen_saturn(lua_State *L) {
    luaL_openlib(L, "saturn", saturn, 0);
    return 1;
}

