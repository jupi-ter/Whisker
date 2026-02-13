#ifndef STMT_H
#define STMT_H

#include "expr.h"
#include "token.h"

typedef struct Stmt Stmt;

typedef enum {
    STMT_EXPRESSION,
    STMT_PRINT,
    STMT_VAR,
    STMT_BLOCK
} StmtType;

typedef struct {
    Expr* expr;
} ExprStmt;

typedef struct {
    Expr* expr;
} PrintStmt;

typedef struct {
    Token name;
    Expr* initializer; // nullable
} VarStmt;

typedef struct {
    Stmt** statements;
    int count;
} BlockStmt;

struct Stmt {
    StmtType type;
    union {
        ExprStmt expr;
        PrintStmt print;
        VarStmt var;
        BlockStmt block;
    } as;
};

Stmt* stmt_expression(Expr* expr);
Stmt* stmt_print(Expr* expr);
Stmt* stmt_var(Token name, Expr* initializer);
Stmt* stmt_block(Stmt** statements, int count);

void stmt_free(Stmt* stmt);

#endif
