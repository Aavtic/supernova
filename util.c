#include "util.h"
#include <malloc.h>
#include <string.h>


char* sized_str_to_str(char* sized_str, size_t n) {
    char* str_p = malloc((sizeof(char) * n) + 1);

    strncpy(str_p, sized_str, n);
    str_p[n] = '\0';

    return str_p;
}
