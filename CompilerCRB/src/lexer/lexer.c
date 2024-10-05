#include "lexer.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// init the lexer

void lexer_init(Lexer *lexer, FILE *source)
{
    lexer->source = source;
    lexer->current_char = fgetc(source);
}

void lexer_advance(Lexer *lexer)
{
    lexer->current_char = fgetc(lexer->source);
}

void lexer_skip_whitespace(Lexer *lexer)
{
    while (isspace(lexer->current_char))
    {
        lexer_advance(lexer);
    }
}

// token from the souce

Token get_next_token(Lexer *lexer)
{
    Token token;
    token.lexeme = malloc(100); // Adjust size as needed

    while (lexer->current_char != EOF)
    {
        if (isspace(lexer->current_char))
        {
            lexer_skip_whitespace(lexer);
            continue;
        }

        if (isdigit(lexer->current_char))
        {
            int i = 0;
            while (isdigit(lexer->current_char))
            {
                token.lexeme[i++] = lexer->current_char;
                lexer_advance(lexer);
            }
            token.lexeme[i] = '\0';
            token.type = TOKEN_INT;
            return token;
        }

        if (isalpha(lexer->current_char))
        {
            int i = 0;
            while (isalnum(lexer->current_char))
            {
                token.lexeme[i++] = lexer->current_char;
                lexer_advance(lexer);
            }
            token.lexeme[i] = '\0';
            token.type = TOKEN_IDENTIFIER;
            return token;
        }

        switch (lexer->current_char)
        {
        case '+':
            token.type = TOKEN_PLUS;
            token.lexeme[0] = '+';
            token.lexeme[1] = '\0';
            lexer_advance(lexer);
            return token;
        case '-':
            token.type = TOKEN_MINUS;
            token.lexeme[0] = '-';
            token.lexeme[1] = '\0';
            lexer_advance(lexer);
            return token;
        case '*':
            token.type = TOKEN_MULTIPLY;
            token.lexeme[0] = '*';
            token.lexeme[1] = '\0';
            lexer_advance(lexer);
            return token;
        case '/':
            token.type = TOKEN_DIVIDE;
            token.lexeme[0] = '/';
            token.lexeme[1] = '\0';
            lexer_advance(lexer);
            return token;
        case '=':
            token.type = TOKEN_ASSIGN;
            token.lexeme[0] = '=';
            token.lexeme[1] = '\0';
            lexer_advance(lexer);
            return token;
        case ';':
            token.type = TOKEN_SEMICOLON;
            token.lexeme[0] = ';';
            token.lexeme[1] = '\0';
            lexer_advance(lexer);
            return token;
        default:
            printf("Unknown character: %c\n", lexer->current_char);
            token.type = TOKEN_EOF;
            token.lexeme[0] = '\0';
            return token;
        }
    }

    // End of file token
    token.type = TOKEN_EOF;
    token.lexeme = strdup("EOF");
    return token;
}