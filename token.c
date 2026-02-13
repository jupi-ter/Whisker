#include "token.h"
#include "error.h"
#include "literal.h"
#include <stdio.h>
#include <stdlib.h>

char* token_type_to_string(TokenType type) {
    switch(type) {
        case TOKEN_LEFT_PAREN:
            return "(";
                break;
        case TOKEN_RIGHT_PAREN:
            return ")";
                break;
        case TOKEN_LEFT_BRACE:
            return "[";
                break;
        case TOKEN_RIGHT_BRACE:
            return "]";
                break;
        case TOKEN_COMMA:
            return ",";
                break;
        case TOKEN_DOT:
            return ".";
                break;
        case TOKEN_MINUS:
            return "-";
                break;
        case TOKEN_PLUS:
            return "+";
                break;
        case TOKEN_SEMICOLON:
            return ";";
                break;
        case TOKEN_SLASH:
            return "/";
                break;
        case TOKEN_STAR:
            return "*";
                break;
        case TOKEN_BANG:
            return "!";
                break;
        case TOKEN_BANG_EQUAL:
            return "!=";
                break;
        case TOKEN_EQUAL:
            return "=";
                break;
        case TOKEN_EQUAL_EQUAL:
            return "==";
                break;
        case TOKEN_GREATER:
            return ">";
                break;
        case TOKEN_GREATER_EQUAL:
            return ">=";
                break;
        case TOKEN_LESS:
            return "<";
                break;
        case TOKEN_LESS_EQUAL:
            return "<=";
                break;
        case TOKEN_IDENTIFIER:
            return "identifier";
                break;
        case TOKEN_STRING:
            return "string";
                break;
        case TOKEN_NUMBER:
            return "number";
                break;
        case TOKEN_AND:
            return "and";
                break;
        case TOKEN_CLASS:
            return "class";
                break;
        case TOKEN_ELSE:
            return "else";
                break;
        case TOKEN_FALSE:
            return "false";
                break;
        case TOKEN_FUN:
            return "fun";
                break;
        case TOKEN_FOR:
            return "for";
                break;
        case TOKEN_IF:
            return "if";
                break;
        case TOKEN_NIL:
            return "nil";
                break;
        case TOKEN_OR:
            return "or";
                break;
        case TOKEN_PRINT:
            return "print";
                break;
        case TOKEN_RETURN:
            return "return";
                break;
        case TOKEN_SUPER:
            return "super";
                break;
        case TOKEN_THIS:
            return "this";
                break;
        case TOKEN_TRUE:
            return "true";
                break;
        case TOKEN_VAR:
            return "var";
                break;
        case TOKEN_WHILE:
            return "while";
                break;
        case TOKEN_EOF:
            return "eof";
                break;
    }
    return "";
}

char* token_to_string(Token token) {
    static char buffer[256];
    sprintf(buffer, "%s %s %s", token_type_to_string(token.type), token.lexeme, literal_to_string(token.literal));

    return buffer;
}

TokenList create_token_list(int capacity) {
    TokenList tokens = {0};
    tokens.count = 0;
    tokens.capacity = capacity;
    tokens.data = malloc(sizeof(Token) * capacity);
    return tokens;
}

void add_token_list(TokenList *tokens, Token token) {
    if (tokens->count + 1 > tokens->capacity) {
        tokens->capacity *= 2;
        Token* new_data = realloc(tokens->data, sizeof(Token) * tokens->capacity);

        if (!new_data) {
            error("Memory reallocation failed.");
        }

        tokens->data = new_data;
    }

    tokens->data[tokens->count++] = token;
}

void free_token_list(TokenList *tokens) {
    for (int i = 0; i < tokens->count; i++) {
        Token* token = &tokens->data[i];
        free(token->lexeme);
        if (token->literal.type == LITERAL_STRING) {
            free(token->literal.as.string);
        }
    }
    free(tokens->data);
    tokens->data = NULL;
    tokens->count = 0;
    tokens->capacity = 0;
}
