#ifndef PARSER_H
#define PARSER_H

#include "../../include/token.h"
#include "../lexer/lexer.h"
#include "../ast/ast.h"

typedef struct
{
    Lexer *lexer;
    Token current_token;
} Parser;

void parser_init(Parser *parser, Lexer *lexer);

ASTNode *parse_program(Parser *parser);

#endif