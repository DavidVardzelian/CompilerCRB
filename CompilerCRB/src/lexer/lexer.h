#ifndef LEXER_H
#define LEXER_H

#include "../../include/token.h"
#include <stdio.h>

typedef struct
{
    FILE *source;
    int current_char;
} Lexer;

void lexer_init(Lexer *lexer, FILE *source);

// token from the source
Token get_next_token(Lexer *lexer);

#endif
