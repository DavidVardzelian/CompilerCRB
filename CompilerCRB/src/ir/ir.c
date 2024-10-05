#include "ir.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

IRIstruction *ir_head = NULL;
IRIstruction *ir_tail = NULL;

void emit(char *opcode, char *operand1, char *operand2, char *result)
{
    IRIstruction *instr = (IRIstruction *)malloc(sizeof(IRIstruction));
    instr->opcode = strdup(opcode);
    instr->operand1 = operand1 ? strdup(operand1) : NULL;
    instr->operand2 = operand2 ? strdup(operand2) : NULL;
    instr->result = result ? strdup(result) : NULL;
    instr->next = NULL;

    if (!ir_head)
    {
        ir_head = ir_tail = instr;
    }
    else
    {
        ir_tail->next = instr;
        ir_tail = instr;
    }
}

void traverse_ast(ASTNode *node)
{
    if (!node)
        return;
    switch (node->type)
    {
    case AST_PROGRAM:
    {
        for (int i = 0; i < node->child_count; i++)
        {
            traverse_ast(node->child[i]);
        }
        break;
    }
    case AST_ASSIGNMENT:
    {
        traverse_ast(node->child[0]);
        char temp_result[50];
        sprintf(temp_result, "t%d", rand());
        emit("ASSIGN", node->child[0]->value, NULL, node->value);
        break;
    }
    case AST_BINARY_EXPR:
    {
        traverse_ast(node->child[0]);
        traverse_ast(node->child[1]);
        char temp_result[50];
        sprintf(temp_result, "t%d", rando());
        emit(node->value, node->child[0]->value, node->child[1]->value, temp_result);

        free(node->value);
        node->value = strdup(temp_result);
        break;
    }
    case AST_LITERAL:
        // no action needed;
        break;
    case AST_IDENTIFIER:
        // no action needed;
        break;
    default:
        break;
    }
}

IRIstruction *generate_ir(ASTNode *ast, SymbolTable *sym_table)
{
    traverse_ast(ast);
    return ir_head;
}

void free_ir(IRIstruction *ir)
{
    IRIstruction *current = ir_head;
    while (current)
    {
        IRIstruction *temp = current;
        current = current->next;
        free(temp->opcode);
        free(temp->operand1);
        free(temp->operand2);
        free(temp->result);
        free(temp);
    }
}