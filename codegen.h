#ifndef CODEGEN_H
#define CODEGEN_H

#include "stmt.h"
#include "expr.h"

typedef struct {
    char* output;
    int capacity;
    int length;
    int indent_level;
} CodeGen;

CodeGen codegen_create(void);
void codegen_free(CodeGen* gen);
void codegen_generate(CodeGen* gen, Stmt** statements, int count);
char* codegen_get_output(CodeGen* gen);

#endif