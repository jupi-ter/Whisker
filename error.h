#ifndef ERROR_H
#define ERROR_H
#include "token.h"

void error(const char* message);
void error_at_line(int line, const char* message);
void error_at_token(Token* token, const char* message);

#endif
