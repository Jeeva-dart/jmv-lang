#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "token.h"

#define MAX_TOKEN_SIZE 100

Token tokens[MAX_TOKEN_SIZE];
int token_count = 0;

void print_token(const char* type, const char* value) {
    printf("%s(%s)\n", type, value);
}

int is_keyword(const char* word) {
    return strcmp(word, "int") == 0 || strcmp(word, "print") == 0;
}

void add_token(TokenType type, const char* value) {
    if (token_count < MAX_TOKEN_SIZE) {
       Token t;
       t.type = type;
       strncpy(t.value, value, sizeof(t.value) - 1);
       tokens[token_count++] = t;
    } else {
        fprintf(stderr, "Token buffer overflow\n");
    }
}

void tokenize(const char* code) {
    int i = 0;
    while (code[i] != '\0') {
        if(isspace(code[i])) {
            i++;
            continue;
        }
        
        // Identifiers and keywords
        if(isalpha(code[i])) {
            char buffer[100];
            int j = 0;

            while(isalnum(code[i])) {
                buffer[j++] = code[i++];
            }
            buffer[j++] = '\0';
            if(is_keyword(buffer))
                add_token(TOKEN_KEYWORD, buffer);
            else 
                add_token(TOKEN_IDENTIFIER, buffer);
        }

        // Numbers
        else if(isdigit(code[i])) {
            char buffer[100];
            int j = 0;
            while(isdigit(code[i])) {
                buffer[j++] = code [i++];
            }
            buffer[j] = '\0';
            add_token(TOKEN_NUMBER, buffer);
        }

        // Operators
        else if(strchr("+-*/=", code[i])) {
            char op[2] = {
                code[i], '\0'
            };
            add_token(TOKEN_OPERATOR, op);
            i++;
        }

        // Delimiters
        else if (strchr("();", code[i])) {
            char delim[2] = {
                code[i], '\0'
            };
            add_token(TOKEN_DELIMITER, delim);
            i++;
        }

        // Unknown characters
        else {
            printf("Unknown character: %c\n", code[i]);
            i++;
        }
    }
    add_token(TOKEN_EOF, "EOF");
}