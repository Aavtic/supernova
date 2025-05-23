#ifndef LEXER_H_
#define LEXER_H_

#include <stddef.h>
#include "dyna.h"

typedef enum {
    TOKEN_END = 0,
    TOKEN_INVALID,
    TOKEN_DEFINER,
    TOKEN_VALUE,
    TOKEN_CURLY_OPEN,
    TOKEN_CURLY_CLOSE,
} TokenType;

// TODO: Add line number and column for error handling in parser
typedef struct {
    TokenType kind;
    char* text;
    size_t text_len;
} Token;


// Dynamic array to hold the tokens
DYNA_INIT(Token) Dyna;

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
