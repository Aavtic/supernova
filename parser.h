#ifndef PARSER_H_
#define PARSER_H_

#include "lexer.h"
#include "semantic.h"


typedef enum NodeKind {
    HEAD,


		SUB_TITLE,
		MAIN_TITLE,
		TITLE,
		DESCRIPTION,
		LINK,
		CODE,
		H1,
		H2,
		H3,
		H4,
		H5,
		H6,
		INJECT,
		ENCLOSE,


    RAW_VALUE,

} NodeKind;

char* get_nodekind_name(NodeKind kind);

#define ALL_DEFINER_STRING "SUB_TITLE, MAIN_TITLE, TITLE, DESCRIPTION, LINK, CODE, H1, H2, H3, H4, H5, H6, INJECT, ENCLOSE"


typedef enum DataType {
    CLASS_NAME,
    ID,
    STYLES,

    RAW_DATA,
} DataType;

typedef struct Data {
    DataType type;
    char* data;
} Data;

typedef struct ParseTree ParseTree;
struct ParseTree {
    NodeKind kind;
    ParseTree* child;
    ParseTree* sibling;
    Data data;
};


typedef struct TokenLL TokenLL;
struct TokenLL {
    Token value;
    TokenLL *next;
};


ParseTree* parse_tokens(TokenLL* tokenll);


#endif // PARSER_H_
