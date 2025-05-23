#ifndef SEMANTIC_H_
#define SEMANTIC_H_

// ERRORS
#define ERROR -1
#define ERROR_CURLY_BRACKET_NOT_OPEN -2
#define ERROR_CURLY_BRACKET_NOT_CLOSE -3
#define ERROR_NO_BODY_FOUND -4
#define ERROR_UNKNOWN_DEFINER -5
#define ERROR_MEMORY_ERROR -6


void print_error_msg(int error_code);
void exit_with_error_msg(int error_code);

#endif  // SEMANTIC_H_
