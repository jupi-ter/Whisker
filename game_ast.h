#ifndef GAME_AST_H
#define GAME_AST_H

#include "token.h"

typedef struct {
    Token entity_name;
    float x;
    float y;
} SpawnCall;

typedef struct {
    SpawnCall* spawns;
    int spawn_count;
} GameDecl;

GameDecl* game_decl_create(SpawnCall* spawns, int spawn_count);
void game_decl_free(GameDecl* game);

#endif
