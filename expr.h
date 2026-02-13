#ifndef EXPR_H
#define EXPR_H

#include "token.h"
#include "literal.h"

typedef struct Expr Expr;

typedef enum {
    EXPR_BINARY,
    EXPR_UNARY,
    EXPR_LITERAL,
    EXPR_GROUPING,
    EXPR_VARIABLE,
    EXPR_ASSIGN
} ExprType;

typedef struct {
    Expr* left;
    Token oprt; //operator, clang is reading this as the cpp operator keyword.
    Expr* right;
} BinaryExpr;

typedef struct {
    Token oprt;
    Expr* right;
} UnaryExpr;

typedef struct {
    Literal value;
} LiteralExpr;

typedef struct {
    Expr* expression;  
} GroupingExpr;

typedef struct {
    Token name;
} VariableExpr;

typedef struct {
    Token name;
    Expr* value;
} AssignExpr;

struct Expr {
    ExprType type;
    union {
        BinaryExpr binary;
        UnaryExpr unary;
        LiteralExpr literal;
        GroupingExpr grouping;
        VariableExpr variable;
        AssignExpr assign;
    } as;
};

Expr* expr_binary(Expr* left, Token oprt, Expr* right);
Expr* expr_unary(Token oprt, Expr* right);
Expr* expr_literal(Literal value);
Expr* expr_grouping(Expr* expression);
Expr* expr_variable(Token name);
Expr* expr_assign(Token name, Expr* value);
void expr_free(Expr* expr);

#endif
