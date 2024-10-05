#ifndef IR_H
#define IR_H

#include "../ast/ast.h"
#include "../semantic/symbol_table.h"

typedef struct
{
    char *opcode;
    char *operand1;
    char *operand2;
    char *result;
    struct IRIstruction *next;
} IRIstruction;

IRInstruction *generate_ir(ASTNode *ast, SymbolTable *symbol_table);

void free_ir(IRInstruction *ir);