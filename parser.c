#include "parser.h"
#include "lexer.h"
#include "string.h"
#include "semantic.h"
#include "util.h"
#include "stdbool.h"



char* get_nodekind_name(NodeKind kind) {
    switch (kind) {
        case HEAD:
            return "HEAD";
        case SUB_TITLE:
            return "SUB_TITLE";
        case MAIN_TITLE:
            return "MAIN_TITLE";
        case TITLE:
            return "TITLE";
        case DESCRIPTION:
            return "DESCRIPTION";
        case LINK:
            return "LINK";
        case CODE:
            return "CODE";
        case H1:
            return "H1";
        case H2:
            return "H2";
        case H3:
            return "H3";
        case H4:
            return "H4";
        case H5:
            return "H5";
        case H6:
            return "H6";
        case INJECT:
            return "INJECT";
        case ENCLOSE:
            return "ENCLOSE";
        case RAW_VALUE:
            return "RAW_VALUE";
    }
    return 0;
}




ParseTree* new_parse_tree() {
    ParseTree* tree = malloc(sizeof(ParseTree));

    if (tree == NULL) {
        exit_with_error_msg(ERROR_MEMORY_ERROR);
    }

    return tree;
}

ParseTree* add_child(ParseTree* parsetree, ParseTree* child) {
    parsetree->child = child;
    return parsetree->child;
}
ParseTree* add_sibling(ParseTree* parsetree, ParseTree* sibling) {
    parsetree->sibling = sibling;
    return parsetree->sibling;
}


bool verify_valid_definer(char* definer_str, size_t n, NodeKind* kind) {
    if (strncmp("@sub_title", definer_str, n) == 0) {
        *kind = SUB_TITLE;
    }
    else if  (strncmp("@main_title", definer_str, n) == 0) {
        *kind = MAIN_TITLE;
    }
    else if  (strncmp("@title", definer_str, n) == 0) {
        *kind = TITLE;
    }
    else if  (strncmp("@description", definer_str, n) == 0) {
        *kind = DESCRIPTION;
    }
    else if  (strncmp("@link", definer_str, n) == 0) {
        *kind = LINK;
    }
    else if  (strncmp("@code", definer_str, n) == 0) {
        *kind = CODE;
    }
    else if  (strncmp("@h1", definer_str, n) == 0) {
        *kind = H1;
    }
    else if  (strncmp("@h2", definer_str, n) == 0) {
        *kind = H2;
    }
    else if  (strncmp("@h3", definer_str, n) == 0) {
        *kind = H3;
    }
    else if  (strncmp("@h4", definer_str, n) == 0) {
        *kind = H4;
    }
    else if  (strncmp("@h5", definer_str, n) == 0) {
        *kind = H5;
    }
    else if  (strncmp("@h6", definer_str, n) == 0) {
        *kind = H6;
    }
    else if  (strncmp("@inject", definer_str, n) == 0) {
        *kind = INJECT;
    }
    else if  (strncmp("@enclose", definer_str, n) == 0) {
        *kind = ENCLOSE;
    }

    else {
        return false;
    }

    return true;
}


TokenLL* parse_childrens(ParseTree* tree, TokenLL* head) {
    Token t;
    t = head->value;

    if (head == NULL) {
        fprintf(stderr, "ERROR: Expected Open Curly '{' but not provided");
        exit_with_error_msg(ERROR_CURLY_BRACKET_NOT_OPEN);
    }

    // Ignore the token if the token is a value.
    // It will be grabbed in the upcoming loop.
    // Othersize if it is something otherthan value and open_curly exit with error
    // 
    // Purposefully not incrementing the head, because if the head is at value it should 
    // not be incremented
    if (t.kind == TOKEN_VALUE){
    } else if (t.kind != TOKEN_CURLY_OPEN) {
        fprintf(stderr, "ERROR: Expected Open Curly '{' but found %.*s", (int)t.text_len, t.text);
        exit_with_error_msg(ERROR_CURLY_BRACKET_NOT_OPEN);
    }

    
    while (head != NULL && t.kind != TOKEN_CURLY_CLOSE) {
        NodeKind kind;
        ParseTree* sibling = new_parse_tree();

        if (t.kind == TOKEN_DEFINER) {

            if (!verify_valid_definer(t.text, t.text_len, &kind)) {
                // No tokens matched
                // TODO: Add line number and column for error handling in parser
                fprintf(stderr, "ERROR: Expected one of: %s\nFound: %.*s\n", ALL_DEFINER_STRING, (int) t.text_len, t.text);
                exit_with_error_msg(ERROR_UNKNOWN_DEFINER);
            }

            printf("identifier: %s\n", get_nodekind_name(kind));

            sibling->kind = kind;
            tree->sibling = sibling;

            //
            // Check for the following contents withing
            // Open and close brackets
            //

            ParseTree* child = new_parse_tree();
            head = parse_childrens(child, head->next);

            tree->child = child;
        }

        if (t.kind == TOKEN_VALUE) {
            kind = RAW_VALUE;

            Data data;
            data.data = sized_str_to_str(t.text, t.text_len);
            data.type = RAW_DATA;

            printf("value: %s\n", data.data);

            tree->data = data;

            tree->kind = kind;
        }

        head = head->next;
        t = head->value;
    }

    if (head == NULL) {
        fprintf(stderr, "ERROR: Expected Close Curly '}' but not provided\n");
        exit_with_error_msg(ERROR_CURLY_BRACKET_NOT_CLOSE);
    }

    // Not Incrementing the closed curly
    // head = head->next;

    return head;
}

ParseTree* parse_tokens(TokenLL* tokenll) {
    ParseTree* tree = new_parse_tree();
    ParseTree* sibling;
    tree->kind = HEAD;

    TokenLL* head = tokenll;

    Token t;

    while (head != NULL) {
        t = head->value;
        sibling = new_parse_tree();
        if (t.kind == TOKEN_DEFINER) {
            NodeKind kind;
            if (!verify_valid_definer(t.text, t.text_len, &kind)) {
                // No tokens matched
                // TODO: Add line number and column for error handling in parser
                fprintf(stderr, "ERROR: Expected one of: %s\nFound: %.*s\n", ALL_DEFINER_STRING, (int) t.text_len, t.text);
                exit_with_error_msg(ERROR_UNKNOWN_DEFINER);
            }

            sibling->kind = kind;

            printf("**************************************************************\n");
            printf("DEFINER: %s\n", get_nodekind_name(kind));
            
            // Get the child
            ParseTree* child = new_parse_tree();

            printf("CHILDREN(S):\n");
            head = parse_childrens(child, head->next);

            printf("**************************************************************\n");

            sibling->child = child;
            tree->sibling = sibling;
        } else {
            printf("TOKEN: %s\n", get_token_name(t.kind));
            printf("value: %s\n", t.text);
            UNREACHABLE("Error in parsing");
        }

        head = head->next;
    }

    return tree;
}
