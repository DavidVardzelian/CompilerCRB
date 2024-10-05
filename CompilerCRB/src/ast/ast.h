#ifndef AST_H
#define AST_H

#include <stdlib.h>

typedef enum
{
    AST_PROGRAM,
    AST_ASSIGNMENT,
    AST_BINARY_EXPR,
    AST_LITERAL,
    AST_IDENTIFIER
} ASTNodeType;

// forward declaration
typedef struct ASTNode ASTNode;

struct ASTNode
{
    ASTNodeType type;
    char *value;
    ASTNode **child;
    int child_count;
};

ASTNode *create_ast_node(ASTNodeType type, char *value);

void add_child(ASTNode *parent, ASTNode *child);

void free_ast(ASTNode *node);

#endif