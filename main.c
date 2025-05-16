#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"


char* read_entire_file(char* filename) {  
    FILE* file_ptr = fopen(filename, "r");

    if (file_ptr == NULL) {
        perror("ERROR: Could not read file");
        fclose(file_ptr);
        exit(1);
    }

    unsigned long length;
    fseek(file_ptr, 0, SEEK_END);
    length = ftell(file_ptr);
    rewind(file_ptr);

    char* buffer = malloc(length);
    fread(buffer, 1, length, file_ptr);

    fclose(file_ptr);

    return buffer;
}


int main() {
    char* file_name = "document.supd";
    char* text = read_entire_file(file_name);

    Lexer l = lexer_new(text, strlen(text));

    Token t = next_token(&l);
    while (t.kind != TOKEN_END) {
        printf("%.*s: %s\n", (int)t.text_len, t.text, get_token_name(t.kind));
        t = next_token(&l);
    }

    return 0;
}
