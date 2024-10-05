#ifndef TOKEN_H
#define TOKEN_H

typedef enum
{
    TOKEN_INT,
    TOKEN_FLOAT,
    TOKEN_IDENTIFIER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_ASSIGN,
    TOKEN_SEMICOLON,
    TOKEN_EOF
} TokenType;

typedef struct
{
    TokenType type;
    char *lexeme;

} Token;

#endif
