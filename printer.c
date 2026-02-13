#include "printer.h"
#include "literal.h"
#include "token.h"
#include <stdio.h>

static void print_expr_recursive(Expr* expr, int indent) {
 if (!expr) return;
    
    // Print indentation
    for (int i = 0; i < indent; i++) {
        printf("  ");
    }
    
    switch (expr->type) {
        case EXPR_BINARY:
            printf("Binary (%s)\n", token_type_to_string(expr->as.binary.oprt.type));
            print_expr_recursive(expr->as.binary.left, indent + 1);
            print_expr_recursive(expr->as.binary.right, indent + 1);
            break;
            
        case EXPR_UNARY:
            printf("Unary (%s)\n", token_type_to_string(expr->as.unary.oprt.type));
            print_expr_recursive(expr->as.unary.right, indent + 1);
            break;
            
        case EXPR_LITERAL:
            printf("Literal (%s)\n", literal_to_string(expr->as.literal.value));
            break;
            
        case EXPR_GROUPING:
            printf("Grouping\n");
            print_expr_recursive(expr->as.grouping.expression, indent + 1);
            break;
            
        case EXPR_VARIABLE:
            printf("Variable (%s)\n", expr->as.variable.name.lexeme);
            break;
            
        case EXPR_ASSIGN:
            printf("Assign (%s)\n", expr->as.assign.name.lexeme);
            print_expr_recursive(expr->as.assign.value, indent + 1);
            break;
    }
}

void print_ast(Expr* expr) {
    print_expr_recursive(expr, 0);
}