#include "utils.h"
#include "error.h"
#include <string.h>

char* my_strndup(const char* s, size_t n) {
    char* result = malloc(n + 1);
    if (!result) {
        error(error_messages[ERROR_MALLOCFAIL].message);
    }
    memcpy(result, s, n);
    result[n] = '\0';
    return result;
}