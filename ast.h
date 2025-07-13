#ifndef AST_H
#define AST_H

typedef enum {
    AST_NUMBER,
    AST_IDENTIFIER,
    AST_BINARY_OP
} ExprType;

typedef struct ASTExpr {
    ExprType type;

    union {
        struct {
            struct ASTExpr* left;
            char op[2];
            struct ASTExpr* right;
        } binary;

        char identifier[100];
        int number;
    };
} ASTExpr;

typedef enum {
    AST_DECLARATION,
    AST_PRINT
} StmtType;

typedef struct ASTStmt {
    StmtType type;

    union {
        struct {
            char var_name[100];
            ASTExpr* value;
        } declaration;

        struct {
            ASTExpr* expression;
        } print_stmt;
    };
} ASTStmt;

#endif
