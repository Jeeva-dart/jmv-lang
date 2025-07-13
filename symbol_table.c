#include <string.h>
#include <stdio.h>
#include "symbol_table.h"

int symbol_count = 0;

void reset_symbol_table() {
    symbol_count = 0;
}

int is_declared(const char* name) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i].name, name) == 0) {
            return 1;
        }
    }
    return 0;
}

int add_symbol(const char* name) {
    if (is_declared(name)) {
        return 0; // already exists
    }
    strcpy(symbol_table[symbol_count].name, name);
    symbol_table[symbol_count].initialized = 1;
    symbol_count++;
    return 1;
}
