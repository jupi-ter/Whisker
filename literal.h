#ifndef LITERAL_H
#define LITERAL_H

#include <stdbool.h>

typedef enum {
    LITERAL_NONE,
    LITERAL_STRING,
    LITERAL_NUMBER,
    LITERAL_BOOLEAN
} LiteralType;

typedef struct {
    LiteralType type;
    union {
        char* string;
        double number;
        bool boolean;
    } as;
} Literal;

char* literal_to_string(Literal literal);

#endif
