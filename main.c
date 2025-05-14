#include <stdio.h>
#include <string.h>

#include "lexer.h"

int main() {
    char* text = "@title\n"
        "      @another\n"
        "       ";

    Lexer l = lexer_new(text, strlen(text));

    Token t = next_token(&l);
    while (t.kind != TOKEN_END) {
        printf("%.*s: %s\n", (int)t.text_len, t.text, get_token_name(t.kind));
        t = next_token(&l);
    }

    return 0;
}
