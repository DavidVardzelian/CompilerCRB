#include "ast.h"
#include <stdio.h>
#include <string.h>

ASTNode *create_ast_node(ASTNodeType type, char *value)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = type;
    node->value = value ? strdup(value) : NULL;
    node->child = NULL;
    node->child_count = 0;
    return node;
}

void add_child(ASTNode *parent, ASTNode *child)
{
    parent->child_count++;
    parent->child = (ASTNode **)realloc(parent->child, sizeof(ASTNode *) * parent->child_count);
    parent->child[parent->child_count - 1] = child;
}

void free_ast(ASTNode *node)
{
    if (!node)
        return;
    for (int i = 0; i < node->child_count; i++)
    {
        free_ast(node->child[i]);
    }

    free(node->child);
    free(node->value);
    free(node);
}