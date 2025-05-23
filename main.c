#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "parser.h"


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

    // // Dynamic array for tokens;
    // Dyna tokens = {0};
    // tokens.start = malloc(DYNA_INITIAL_CAP * sizeof(Token));
    // tokens.capacity = DYNA_INITIAL_CAP;
    // tokens.size = sizeof(Token);

    TokenLL *head = NULL;
    TokenLL *prev = NULL;

    Token t = next_token(&l);
    while (t.kind != TOKEN_END) {

        TokenLL *new_node = (TokenLL*)malloc(sizeof(TokenLL));
        new_node->value = t;

        if (head == NULL) {
            head = new_node;
            prev = new_node;
        } else {
            prev->next = new_node;
            prev = new_node;
        }

        t = next_token(&l);
        if (t.kind == TOKEN_INVALID) {
            printf("ERROR: Invalid token");
            printf("%.*s: %s\n", (int)t.text_len, t.text, get_token_name(t.kind));
            exit(1);
        }
    }

    TokenLL *temp = head;

    while (temp != NULL) {
        t = temp->value;
        // printf("%.*s: %s\n", (int)t.text_len, t.text, get_token_name(t.kind));
        temp = temp->next;
    }

    parse_tokens(head);

    return 0;
}
