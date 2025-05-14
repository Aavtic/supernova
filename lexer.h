#ifndef LEXER_H_
#define LEXER_H_

#include <stddef.h>

typedef enum {
    TOKEN_END = 0,
    TOKEN_INVALID,
    TOKEN_DEFINER,
    TOKEN_VALUE,
} TokenType;

typedef struct {
    TokenType kind;
    char* text;
    size_t text_len;
} Token;

char* get_token_name(TokenType kind);

typedef struct {
    char* content;
    size_t content_len;
    size_t cursor;
    size_t line;
    size_t bol;
} Lexer;


Lexer lexer_new(char* content, size_t len);
Token next_token(Lexer* l);


Lexer* strip_whitespace_left(Lexer* l);
char consume_char(Lexer* l);


#endif // LEXER_H_
