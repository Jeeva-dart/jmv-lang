#include "token.h"
#include "ast.h"
#include "symbol_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STMTS 100

extern Token tokens[];
extern int token_count;

ASTStmt* ast_statements[MAX_STMTS];
int ast_count = 0;
int current = 0;

Token peek() {
    if (current < token_count) {
        return tokens[current];
    }
    Token eof_token;
    eof_token.type = TOKEN_EOF;
    strcpy(eof_token.value, "EOF");
    return eof_token;
}

Token advance() {
    if (current < token_count) {
        return tokens[current++];
    }
    Token eof_token;
    eof_token.type = TOKEN_EOF;
    strcpy(eof_token.value, "EOF");
    return eof_token;
}

int match(TokenType type, const char* value) {
    if(peek().type == type && (value == NULL || strcmp(peek().value, value) == 0)) {
        advance();
        return 1;
    }
    return 0;
}

void error(const char* message) {
    fprintf(stderr, "Error: %s at token '%s'\n", message, peek().value);
    exit(EXIT_FAILURE);
}

void statement();
ASTExpr* expression();
void print_ast();

void program() {
    while (peek().type != TOKEN_EOF) {
        statement();
    }
}

void statement() {
    if (match(TOKEN_KEYWORD, "int")) {
        if (peek().type != TOKEN_IDENTIFIER) error("Expected variable name");
        Token var = advance();
        if (!add_symbol(var.value)) {
            char msg[200];
            sprintf(msg, "Duplicate variable declaration: %s", var.value);
            error(msg);
        }

        if (!match(TOKEN_OPERATOR, "=")) error("Expected '='");
        
        ASTExpr* expr = expression();

        if (!match(TOKEN_DELIMITER, ";")) error("Expected ';'");
        ASTStmt* stmt = malloc(sizeof(ASTStmt));
        stmt->type = AST_DECLARATION;
        strcpy(stmt->declaration.var_name, var.value);
        stmt->declaration.value = expr;

        ast_statements[ast_count++] = stmt;
    }
    else if (match(TOKEN_KEYWORD, "print")) {
        if (!match(TOKEN_DELIMITER, "(")) error("Expected '(' after print");
        ASTExpr* expr = expression();
        if (!match(TOKEN_DELIMITER, ")")) error("Expected ')'");
        if (!match(TOKEN_DELIMITER, ";")) error("Expected ';'");
        ASTStmt* stmt = malloc(sizeof(ASTStmt));
        stmt->type = AST_PRINT;
        stmt->print_stmt.expression = expr;

        ast_statements[ast_count++] = stmt;
    }
    else {
        error("Unknown statement");
    }
}

ASTExpr* expression() {
    ASTExpr* left;

    if (peek().type == TOKEN_NUMBER) {
        left = malloc(sizeof(ASTExpr));
        left->type = AST_NUMBER;
        left->number = atoi(advance().value);
    } else if (peek().type == TOKEN_IDENTIFIER) {
        Token id = advance();
        if (!is_declared(id.value)) {
            char msg[200];
            sprintf(msg, "Use of undeclared variable: %s", id.value);
            error(msg);
        }

        ASTExpr* expr = malloc(sizeof(ASTExpr));
        expr->type = AST_IDENTIFIER;
        strcpy(expr->identifier, id.value);
        return expr;
    } else {
        error("Expected number or identifier");
    }

    // Handle binary expressions: a + b, 5 + 3
    while (match(TOKEN_OPERATOR, "+") || match(TOKEN_OPERATOR, "-")) {
        char op[2];
        strcpy(op, tokens[current - 1].value); // just matched + or -

        ASTExpr* right;

        if (peek().type == TOKEN_NUMBER) {
            right = malloc(sizeof(ASTExpr));
            right->type = AST_NUMBER;
            right->number = atoi(advance().value);
        } else if (peek().type == TOKEN_IDENTIFIER) {
            right = malloc(sizeof(ASTExpr));
            right->type = AST_IDENTIFIER;
            strcpy(right->identifier, advance().value);
        } else {
            error("Expected number or identifier after operator");
        }

        // Create binary op node
        ASTExpr* bin = malloc(sizeof(ASTExpr));
        bin->type = AST_BINARY_OP;
        bin->binary.left = left;
        strcpy(bin->binary.op, op);
        bin->binary.right = right;

        left = bin;  // chain expressions
    }

    return left;
}

void print_expr(ASTExpr* expr) {
    if (expr->type == AST_NUMBER) {
        printf("%d", expr->number);
    } else if (expr->type == AST_IDENTIFIER) {
        printf("%s", expr->identifier);
    } else if (expr->type == AST_BINARY_OP) {
        printf("(");
        print_expr(expr->binary.left);
        printf(" %s ", expr->binary.op);
        print_expr(expr->binary.right);
        printf(")");
    }
}

void print_ast() {
    for (int i = 0; i < ast_count; i++) {
        ASTStmt* stmt = ast_statements[i];
        if (stmt->type == AST_DECLARATION) {
            printf("Declare %s = ", stmt->declaration.var_name);
            print_expr(stmt->declaration.value);
            printf(";\n");
        } else if (stmt->type == AST_PRINT) {
            printf("Print: ");
            print_expr(stmt->print_stmt.expression);
            printf(";\n");
        }
    }
}
