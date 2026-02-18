#ifndef PARSER_H
#define PARSER_H

#include "entity_ast.h"
#include "token.h"
#include "expr.h"
#include "stmt.h"
#include "game_ast.h"

typedef struct {
    Token* tokens;
    int current;
    int count;
} Parser;

typedef struct {
    Stmt** statements;
    int count;
    EntityDecl** entities;
    int entity_count;
    GameDecl* game; // nullable
} Program;

Parser parser_create(TokenList tokens);
Program parse(Parser* parser);
void free_program(Program* prog);

#endif