#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    TOKEN_KEYWORD,   // int, print
    TOKEN_IDENTIFIER, // Variable names
    TOKEN_NUMBER,    // Numeric literals
    TOKEN_OPERATOR,  // +, -, *, /
    TOKEN_DELIMITER, // ;, ,, (, )
    TOKEN_EOF,      // End of file
    TOKEN_UNKNOWN
} TokenType;

typedef struct {
    TokenType type;
    char value[100];
} Token;

#endif // TOKEN_H