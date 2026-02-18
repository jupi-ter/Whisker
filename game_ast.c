#include "game_ast.h"
#include "error.h"
#include <stdlib.h>

GameDecl* game_decl_create(SpawnCall* spawns, int spawn_count) {
    GameDecl* game = malloc(sizeof(GameDecl));
    if (!game) error(error_messages[ERROR_MALLOCFAIL].message);
    
    game->spawns = spawns;
    game->spawn_count = spawn_count;
    return game;
}

void game_decl_free(GameDecl* game) {
    if (!game) return;
    free(game->spawns);
    free(game);
}
