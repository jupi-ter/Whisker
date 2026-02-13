#ifndef SCANNER_H
#define SCANNER_H

#include "token.h"

typedef struct {
    char* source;
    TokenList tokens;
    int start;
    int current;
    int line;
} Scanner;

Scanner scanner_create(char* source);
char advance(Scanner* scanner);
void scan_token(Scanner *scanner);
TokenList scan_tokens(Scanner* scanner);

#endif
