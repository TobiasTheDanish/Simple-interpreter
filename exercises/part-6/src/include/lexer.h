#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include <stddef.h>
typedef struct LEXER_S
{
	char* contents;
	size_t pos;
	char current_char;
} lexer_t;

lexer_t* lexer_new(char* contents);

void lexer_advance(lexer_t* l);

void lexer_skip_whitespace(lexer_t* l);

token_t* lexer_get_next_token(lexer_t* l);

token_t* lexer_collect_string(lexer_t* l);

token_t* lexer_collect_integer(lexer_t* l);

#endif // !LEXER_H
