#include <stdio.h>
#include <stdlib.h>

#include "Lexer/lexer.h"
#include "Parser/parser.h"
#include "AST/ast.h"
#include "Semantic/symbol_table.h"
#include "IR/ir.h"
#include "CodeGen/codegen.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <sourcefile> \n", argv[0]);
        return 1;
    }

    FILE *source = fopen(argv[1], "r");
    if (!source)
    {
        printf("Error: Could not open source file %s\n", argv[2]);
        return 1;
    }
    Lexer lexer;
    lexer_init(&lexer, source);

    Parser parser;
    parser_init(&parser, &lexer);

    ASTNode *ast = parse_program(&parser);
    if (!ast)
    {
        printf("Error: Parsing failed.\n");
        fclose(source);
        return 1;
    }

    SymbolTable *sym_table = create_symbol_table();
    perform_semantic_analysis(ast, sym_table);

    IRIstruction *ir = generate_ir(ast, sym_table);

    generate_code(ir);

    fclose(source);
    free_ast(ast);
    free_symbol_table(sym_table);
    free_ir(ir);

    return 0;
}