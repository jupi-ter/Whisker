#include "utils.h"
#include "error.h"
#include <string.h>

char* my_strndup(const char* s, size_t n) {
    char* result = malloc(n + 1);
    if (!result) {
        error("Memory allocation failed.");
    }
    memcpy(result, s, n);
    result[n] = '\0';
    return result;
}