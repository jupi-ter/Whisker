#include "literal.h"
#include <stdio.h>

char* literal_to_string(Literal literal) {
    switch (literal.type) {
        case LITERAL_NONE:
            return "none";
            break;
        case LITERAL_BOOLEAN:
            return literal.as.boolean ? "true" : "false";
            break;
        case LITERAL_NUMBER:
            ;
            static char buf[32];
            sprintf(buf, "%f", literal.as.number);
            return buf;
            break;
        case LITERAL_STRING:
            return literal.as.string;
            break;
    }
    return "";
}
