#include <stdio.h>
#include <stdlib.h>

#include "semantic.h"
#include "parser.h"
#include "lexer.h"

void print_error_msg(int error_code) {
    switch (error_code) {
        case ERROR_CURLY_BRACKET_NOT_OPEN:
            printf("ERROR: Curly bracket not open");
            break;
        case ERROR_CURLY_BRACKET_NOT_CLOSE:
            printf("ERROR: Curly bracket not closed");
            break;
        default:
            printf("Invalid error code %d", error_code);
            break;
    }
}


void exit_with_error_msg(int error_code) {
    switch (error_code) {
        case ERROR_CURLY_BRACKET_NOT_OPEN:
            fprintf(stderr, "ERROR: Curly bracket not open\n");
            break;
        case ERROR_CURLY_BRACKET_NOT_CLOSE:
            fprintf(stderr, "ERROR: Curly bracket not closed\n");
            break;
        case ERROR_UNKNOWN_DEFINER:
            fprintf(stderr, "ERROR: Unknown Definer\n");
            break;
        case ERROR_MEMORY_ERROR:
            fprintf(stderr, "ERROR! Insufficient Memory!\nDownload more RAM please\n");
            break;
        default:
            fprintf(stderr, "Invalid error code %d\n", error_code);
            exit(ERROR);
            break;
    }

    exit(error_code);
}
