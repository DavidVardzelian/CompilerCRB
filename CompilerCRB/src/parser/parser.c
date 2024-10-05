#include "parser.h"
#include "../ast/ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ASTNode *parse_statement(Parser *parser);
ASTNode *parse_expression(Parser *parser);

void parser_init(Parser *parser, Lexer *lexer)
{
    parser->lexer = lexer;
    parser->current_token = get_next_token(parser->lexer);
}

void parser_eat(Parser *parser, TokenType type)
{
    if (parser->current_token.type == type)
    {
        // free lexeme of the current toekn
        free(parser->current_token.lexeme);
        parser->current_token = get_next_token(parser->lexer);
    }
    else
    {
        printf("Syntax error: Unexpected toekn %s \n", parser->current_token.lexeme);
        exit(1);
    }
}

ASTNode *parse_program(Parser *parser)
{
    ASTNode *root = create_ast_node(AST_PROGRAM, NULL);
    root->child = NULL;

    while (parser->current_token.type != TOKEN_EOF)
    {
        ASTNode *stmt = parse_statement(parser);
        add_child(root, stmt);
    }

    return root;
}

ASTNode *parse_statement(Parser *parser)
{
    if (parser->current_token.type == TOKEN_IDENTIFIER)
    {
        char *var_name = strdup(parser->current_token.lexeme);
        parser_eat(parser, TOKEN_IDENTIFIER);

        if (parser->current_token.type != TOKEN_ASSIGN)
        {
            printf("Syntax error: Expeted '=' after identifier.\n");
            exit(1);
        }
        parser_eat(parser, TOKEN_ASSIGN);

        ASTNode *expr = parse_expression(parser);

        if (parser->current_token.type != TOKEN_SEMICOLON)
        {
            printf("Syntax error: Expected ';' after expression. \n");
            exit(1);
        }

        parser_eat(parser, TOKEN_SEMICOLON);

        ASTNode *assign_node = create_ast_node(AST_ASSIGNMENT, var_name);
        add_child(assign_node, expr);

        return assign_node;
    }
    printf("Syntax error : Unknown statement starting with '%s' \n", parser->current_token.lexeme);
    exit(1);
}

ASTNode *parse_expression(Parser *parser)
{
    ASTNode *left = NULL;
    ASTNode *right = NULL;
    char *operator= NULL;

    // handle left operand
    if (parser->current_token.type == TOKEN_INT)
    {
        left = create_ast_node(AST_LITERAL, parser->current_token.lexeme);
        parser_eat(parser, TOKEN_INT);
    }
    else if (parser->current_token.type == TOKEN_IDENTIFIER)
    {
        left = create_ast_node(AST_IDENTIFIER, parser->current_token.lexeme);
        parser_eat(parser, TOKEN_IDENTIFIER);
    }
    else
    {
        printf("Syntax error: Expected expression. \n");
        exit(1);
    }

    // handle operator
    if (parser->current_token.type == TOKEN_PLUS ||
        parser->current_token.type == TOKEN_MINUS ||
        parser->current_token.type == TOKEN_MULTIPLY ||
        parser->current_token.type == TOKEN_DIVIDE)
    {
        operator= strdup(parser->current_token.lexeme);
        TokenType op_type = parser->current_token.type;
        parser_eat(parser, op_type);
    }
    else
    {
        return left;
    }

    // handle right operand
    if (parser->current_token.type == TOKEN_INT)
    {
        right = create_ast_node(AST_LITERAL, parser->current_token.lexeme);
        parser_eat(parser, TOKEN_INT);
    }
    else if (parser->current_token.type == TOKEN_IDENTIFIER)
    {
        right = create_ast_node(AST_IDENTIFIER, parser->current_token.lexeme);
        parser_eat(parser, TOKEN_IDENTIFIER);
    }
    else
    {
        printf("Syntax error: Expected expression after operator.\n");
        exit(1);
    }

    ASTNode *expr_node = create_ast_node(AST_BINARY_EXPR, operator);
    add_child(expr_node, left);
    add_child(expr_node, right);

    return expr_node;
}