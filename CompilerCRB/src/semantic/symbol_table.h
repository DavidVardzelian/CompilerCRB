#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdlib.h>
#include "../AST/ast.h"
typedef struct Symbol
{
    char *name;
    char *type;
    struct Symbol *next;
} Symbol;

typedef struct
{
    Symbol *head;
} SymbolTable;

SymbolTable *create_symbol_table();

void add_symbol(SymbolTable *table, const char *name, const char *type);

Symbol *lookup_symbol(SymbolTable *table, const char *name);

void free_symbol_table(SymbolTable *table);

void perform_semantic_analysis(struct ASTNode *ast, SymbolTable *table);

#endif
