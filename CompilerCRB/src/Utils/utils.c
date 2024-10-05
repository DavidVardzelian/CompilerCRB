#include "utils.h"
#include <stdio.h>

// Recursive function to print the AST
void print_ast(ASTNode *node, int depth)
{
    if (!node)
        return;

    for (int i = 0; i < depth; i++)
    {
        printf("  ");
    }

    switch (node->type)
    {
    case AST_PROGRAM:
        printf("Program\n");
        break;
    case AST_ASSIGNMENT:
        printf("Assignment: %s\n", node->value);
        break;
    case AST_BINARY_EXPR:
        printf("Binary Expression: %s\n", node->value);
        break;
    case AST_LITERAL:
        printf("Literal: %s\n", node->value);
        break;
    case AST_IDENTIFIER:
        printf("Identifier: %s\n", node->value);
        break;
    default:
        printf("Unknown Node\n");
        break;
    }

    for (int i = 0; i < node->child_count; i++)
    {
        print_ast(node->child[i], depth + 1);
    }
}
