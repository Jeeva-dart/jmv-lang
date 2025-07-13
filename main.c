#include <stdio.h>
#include <stdlib.h>

extern void tokenize(const char* code);
extern void program();  // From parser.c
extern void reset_symbol_table();  // From symbol_table.c
extern void print_ast();  // From parser.c
extern void generate_asm(const char* filename);  // From asmgen.c

int main() {
    FILE* file = fopen("first.jm", "r");
    if (!file) {
        perror("Failed to open first.jm");
        return 1;
    }

    // Get file size
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    // Allocate memory for source code
    char* buffer = (char*)malloc(size + 1);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return 1;
    }

    // Read file into buffer
    fread(buffer, 1, size, file);
    buffer[size] = '\0'; // Null terminate

    fclose(file);

    reset_symbol_table();
    // Tokenize input
    tokenize(buffer);

    program();
    generate_asm("output.s");
    free(buffer);
    return 0;
}
