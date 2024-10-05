#include "symbol_table.h"
#include "../AST/ast.h"
#include <stdio.h>
#include <string.h>

SymbolTable *create_symbol_table()
{
    SymbolTable *table = (SymbolTable *)malloc(sizeof(SymbolTable));
    table->head = NULL;
    return table;
}

void add_symbol(SymbolTable *table, const char *name, const char *type)
{
    // check if symbol already exists
    Symbol *existing = lookup_symbol(table, name);
    if (existing)
    {
        printf("Semantic error: Redeclaration of variable '%s'\n", name);
        exit(1);
    }

    Symbol *sym = (Symbol *)malloc(sizeof(Symbol));
    sym->name = strdup(name);
    sym->type = strdup(type);
    sym->next = table->head;
    table->head = sym;
}

Symbol *lookup_symbol(SymbolTable *table, const char *name)
{
    Symbol *current = table->head;
    while (current)
    {
        if (strcmp(current->name, name) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}

void free_symbol_table(SymbolTable *table)
{
    Symbol *current = table->head;
    while (current)
    {
        Symbol *temp = current;
        current = current->next;
        free(temp->name);
        free(temp->type);
        free(temp);
    }
    free(table);
}

void perform_semantic_analysis(ASTNode *ast, SymbolTable *table)
{
    if (!ast)
        return;

    switch (ast->type)
    {
    case AST_PROGRAM:
        for (int i = 0; i < ast->child_count; i++)
        {
            perform_semantic_analysis(ast->child[i], table);
        }
        break;
    case AST_ASSIGNMENT:
    {
        char *var_name = ast->value;
        Symbol *sym = lookup_symbol(table, var_name);
        if (!sym)
        {
            add_symbol(table, var_name, "int");
        }
        perform_semantic_analysis(ast->child[0], table);
        break;
    }
    case AST_BINARY_EXPR:
        perform_semantic_analysis(ast->child[0], table);
        perform_semantic_analysis(ast->child[1], table);
        break;
    case AST_LITERAL:
        break;
    case AST_IDENTIFIER:
    {
        char *var_name = ast->value;
        Symbol *sym = lookup_symbol(table, var_name);
        if (!sym)
        {
            printf("Semantic error: Undeclared variable '%s'\n", var_name);
            exit(1);
        }
        break;
    }
    default:
        break;
    }
}
