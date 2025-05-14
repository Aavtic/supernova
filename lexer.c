#include <ctype.h>
#include <stdbool.h>
#include <assert.h>

#include "lexer.h"
#include "util.h"

Lexer lexer_new(char* content, size_t len) {
    Lexer l = {0};
    l.content = content;
    l.content_len = len;

    return l;
}

char* get_token_name(TokenType kind) {

    switch (kind) {
        case TOKEN_END:
            assert(1 && "Should not reach here: get_token_name");
            return "End of Tokens";
        case TOKEN_INVALID:
            return "Invalid token";
        case TOKEN_DEFINER:
            return "Definer";
        case TOKEN_VALUE:
            return "Token value";
    }

    return NULL;
}

Lexer* strip_whitespace_left(Lexer* l) {
    while ((l->cursor < l->content_len) && (isspace(l->content[l->cursor]))) {
        UNUSED(consume_char(l));
    }

    return l;
}

char consume_char(Lexer* l) {
    char c = l->content[l->cursor];
    l->cursor++;
    if (c == '\n') {
        l->line++;
        l->bol = l->cursor;
    }

    return c;
}

bool is_definer_start(char c) {
    return c == '@';
}

bool is_identifier_start(char c) {
    return isalpha(c) || c == '_';
}

bool is_identifier(char c) {
    return isalnum(c) || c == '_';
}

#define DOES_NOT_BREAK (l->content[l->cursor] != '\n') && (l->content[l->cursor] != ' ') && (l->content[l->cursor] != '{')
Token next_token(Lexer* l) {
    strip_whitespace_left(l);

    Token token = {
        .text = &l->content[l->cursor],
    };

    if (l->cursor >= l->content_len) return token;

    // Check for definer
    if (is_definer_start(consume_char(l))) {
        if (l->cursor >= l->content_len) {
            token.kind = TOKEN_INVALID;
            token.text_len = 1;
            return token;
        }
        token.text_len += 1;
        char first = consume_char(l);
        if (is_identifier_start(first)) {
            token.text_len += 1;
            while ((l->cursor < l->content_len) && DOES_NOT_BREAK) {
                if (!is_identifier(consume_char(l))) {
                    token.kind = TOKEN_INVALID;
                    token.text_len = 1;
                    return token;
                }
                token.text_len += 1;
            }
            token.kind = TOKEN_DEFINER;
            return token;
        } 
    }

    token.kind = TOKEN_INVALID;
    token.text_len = 1;

    return token;
}
