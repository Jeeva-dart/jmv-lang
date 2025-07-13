#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "symbol_table.h"

extern ASTStmt* ast_statements[];
extern int ast_count;

void emit_expr(FILE* f, ASTExpr* expr) {
    if (expr->type == AST_NUMBER) {
        fprintf(f, "    movl $%d, %%eax\n", expr->number);
    } else if (expr->type == AST_IDENTIFIER) {
        fprintf(f, "    movl %s(%%rip), %%eax\n", expr->identifier);
    } else if (expr->type == AST_BINARY_OP) {
        // evaluate left
        emit_expr(f, expr->binary.left);
        fprintf(f, "    push %%rax\n");

        // evaluate right
        emit_expr(f, expr->binary.right);
        fprintf(f, "    movl %%eax, %%ebx\n");  // move right result to ebx
        fprintf(f, "    pop %%rax\n");          // left result in eax

        if (strcmp(expr->binary.op, "+") == 0) {
            fprintf(f, "    addl %%ebx, %%eax\n");
        } else if (strcmp(expr->binary.op, "-") == 0) {
            fprintf(f, "    subl %%ebx, %%eax\n");
        } else {
            fprintf(f, "    # unsupported operator\n");
        }
    }
}

void generate_asm(const char* filename) {
    FILE* f = fopen(filename, "w");
    if (!f) {
        perror("Cannot open output assembly file");
        return;
    }

    fprintf(f, ".section .data\n");
    fprintf(f, "fmt: .string \"%%d\\n\"\n");

    // Declare global variables
    for (int i = 0; i < ast_count; i++) {
        ASTStmt* stmt = ast_statements[i];
        if (stmt->type == AST_DECLARATION) {
            fprintf(f, "%s: .long 0\n", stmt->declaration.var_name);
        }
    }

    fprintf(f, "\n.section .text\n");
    fprintf(f, ".global main\n");
    fprintf(f, "main:\n");

    for (int i = 0; i < ast_count; i++) {
        ASTStmt* stmt = ast_statements[i];

        if (stmt->type == AST_DECLARATION) {
            emit_expr(f, stmt->declaration.value);
            fprintf(f, "    movl %%eax, %s(%%rip)\n", stmt->declaration.var_name);
        }

        if (stmt->type == AST_PRINT) {
            emit_expr(f, stmt->print_stmt.expression);
            fprintf(f, "    movl %%eax, %%esi\n");
            fprintf(f, "    leaq fmt(%%rip), %%rdi\n");
            fprintf(f, "    movl $0, %%eax\n");
            fprintf(f, "    call printf@PLT\n");
        }
    }

    fprintf(f, "    movl $0, %%eax\n");
    fprintf(f, "    ret\n");

    fclose(f);
    printf("✅ Assembly file generated: %s\n", filename);
}
