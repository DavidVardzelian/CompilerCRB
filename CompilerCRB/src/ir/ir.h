#ifndef IR_H
#define IR_H

#include "../AST/ast.h"
#include "../Semantic/symbol_table.h"

typedef struct
{
    char *opcode;
    char *operand1;
    char *operand2;
    char *result;
    struct IRIstruction *next;
} IRIstruction;

IRIstruction *generate_ir(ASTNode *ast, SymbolTable *sym_table);

void free_ir(IRIstruction *ir);

#endif