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
    struct Node *node = malloc(sizeof(struct Node));
    node->v = v;
    node->next = NULL;
    if (!list->head) {
        list->head = node;
    } else {
        node->next = list->head;
        list->head = node;
    }

    return 0;
}

static int show(lua_State *L) {
    if (!list) {
        fprintf(stderr, "You should first call new()\n");
        return 0;
    }
    struct Node *current = list->head;
    printf("Iterating from head to tail...\n");
    while (current) {
        fprintf(stdout, "%d\n", current->v);
        current = current->next;
    }

    return 0;
}

static const luaL_reg saturn[] = {
    { "new",     new     },
    { "prepend", prepend },
    { "show",    show    },
    { NULL,      NULL    }
};

LUALIB_API int luaopen_saturn(lua_State *L) {
    luaL_openlib(L, "saturn", saturn, 0);
    return 1;
}

