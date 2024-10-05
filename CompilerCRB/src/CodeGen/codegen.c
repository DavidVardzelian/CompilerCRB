#include "codegen.h"
#include <stdio.h>
#include <string.h>

void generate_code(IRIstruction *ir)
{
    FILE *output = fopen("output.asm", "w");
    if (!output)
    {
        printf("Error: Could not create output.asm\n");
        exit(1);
    }

    IRIstruction *current = ir;
    while (current)
    {
        if (strcmp(current->opcode, "ASSIGN") == 0)
        {
            fprintf(output, "MOV %s, %s\n", current->result, current->operand1);
        }
        else if (strcmp(current->opcode, "+") == 0)
        {
            fprintf(output, "ADD %s, %s\n", current->operand1, current->operand2);
            fprintf(output, "MOV %s, ACC\n", current->result); // assume ACC is accumulator
        }
        else if (strcmp(current->opcode, "-") == 0)
        {
            fprintf(output, "SUB %s, %s\n", current->operand1, current->operand2);
            fprintf(output, "MOV %s, ACC\n", current->result);
        }
        else if (strcmp(current->opcode, "*") == 0)
        {
            fprintf(output, "MUL %s, %s\n", current->operand1, current->operand2);
            fprintf(output, "MOV %s, ACC\n", current->result);
        }
        else if (strcmp(current->opcode, "/") == 0)
        {
            fprintf(output, "DIV %s, %s\n", current->operand1, current->operand2);
            fprintf(output, "MOV %s, ACC\n", current->result);
        }
        else
        {
            fprintf(output, "; Unknown opcode: %s\n", current->opcode);
        }
        current = current->next;
    }

    fclose(output);
}
