#ifndef UTIL_H_
#define UTIL_H_

#include <stdio.h>
#include <stdlib.h>

#define UNIMPLEMENTED(...)\
        do {                                                                      \
            printf("%s:%d UNIMPLEMENTED: %s\n", __FILE__, __LINE__, __VA_ARGS__); \
            exit(1);                                                              \
        } while (0)                                                               \


#define UNREACHABLE(...)\
        do {                                                                      \
            printf("%s:%d UNREACHABLE: %s\n", __FILE__, __LINE__, __VA_ARGS__); \
            exit(1);                                                              \
        } while (0)                                                               \


#define UNUSED(x) (void) (x)



char* sized_str_to_str(char* sized_str, size_t n);


#endif // UTIL_H_
