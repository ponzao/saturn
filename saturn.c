#include <lua5.1/lua.h>
#include <lua5.1/lauxlib.h>
#include <lua5.1/lualib.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int v;
    struct Node *next;
};

struct Stack {
    struct Node *head;
};

static struct Stack *stack;

static int new(lua_State *L) {
    stack = malloc(sizeof(struct Stack));

    return 0;
}

static int push(lua_State *L) {
    if (!stack) {
        fprintf(stderr, "You should first call new().\n");
        return 0;
    }
    int v = lua_tonumber(L , -1);
    struct Node *node = malloc(sizeof(struct Node));
    node->v = v;
    node->next = NULL;
    if (!stack->head) {
        stack->head = node;
    } else {
        node->next = stack->head;
        stack->head = node;
    }

    return 0;
}

static int pop(lua_State *L) {
    if (!stack) {
        fprintf(stderr, "Stack is null.\n");
        return 0;
    }
    if (!stack->head) {
        fprintf(stderr, "Stack is empty.\n");
        return 0;
    }
    struct Node *tmp = stack->head;
    int result = tmp->v;
    stack->head = stack->head->next;
    free(tmp);
    tmp = NULL;
    lua_pushnumber(L, result);

    return 1;
}

static int show(lua_State *L) {
    if (!stack) {
        fprintf(stderr, "You should first call new()\n");
        return 0;
    }
    struct Node *current = stack->head;
    printf("Iterating from head to tail...\n");
    while (current) {
        fprintf(stdout, "%d\n", current->v);
        current = current->next;
    }

    return 0;
}

static const luaL_reg saturn[] = {
    { "new",  new  },
    { "push", push },
    { "pop",  pop },
    { "show", show },
    { NULL,   NULL }
};

LUALIB_API int luaopen_saturn(lua_State *L) {
    luaL_openlib(L, "saturn", saturn, 0);
    return 1;
}

