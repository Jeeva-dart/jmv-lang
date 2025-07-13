#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#define MAX_SYMBOLS 100

typedef struct {
    char name[100];
    int initialized;
} Symbol;

Symbol symbol_table[MAX_SYMBOLS];
extern int symbol_count;

int is_declared(const char* name);
int add_symbol(const char* name);
void reset_symbol_table();

#endif
