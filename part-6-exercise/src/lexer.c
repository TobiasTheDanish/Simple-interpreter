#include "include/lexer.h"
#include "include/token.h"
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char* char_to_string(char c)
{
	char* s = calloc(2, sizeof(char));
	s[0] = c;

	return s;
}

token_t* advance_with_token(lexer_t* l, token_t* t)
{
	lexer_advance(l);

	return t;
}

lexer_t* lexer_new(char* contents)
{
	lexer_t* l = malloc(sizeof(lexer_t));
	l->contents = contents;
	l->pos = 0;
	l->current_char = l->contents[l->pos];

	return l;
}

void lexer_advance(lexer_t* l)
{
	l->pos += 1;
	l->current_char = l->contents[l->pos];
}

void lexer_skip_whitespace(lexer_t* l)
{
	while (l->current_char == ' ' || l->current_char == '\n' || l->current_char == '\t') 
	{
		lexer_advance(l);
	}
}

token_t* lexer_get_next_token(lexer_t* l)
{
	lexer_skip_whitespace(l);

	if (l->pos > strlen(l->contents) - 1 || l->current_char == '\0') 
	{
		return token_new(EOF, "\0");
	}

	if (isdigit(l->current_char))
	{
		return lexer_collect_integer(l);
	}

	switch (l->current_char) 
	{
		case '"':
			return lexer_collect_string(l);

		case '+':
			return advance_with_token(l, token_new(PLUS, char_to_string(l->current_char)));

		case '-':
			return advance_with_token(l, token_new(MINUS, char_to_string(l->current_char)));

		case '*':
			return advance_with_token(l, token_new(MULTIPLY, char_to_string(l->current_char)));

		case '/':
			return advance_with_token(l, token_new(DIVIDE, char_to_string(l->current_char)));

		case '(':
			return advance_with_token(l, token_new(LPAREN, char_to_string(l->current_char)));

		case ')':
			return advance_with_token(l, token_new(RPAREN, char_to_string(l->current_char)));

		default:
			return token_new(ILLEGAL, "");
	}
}

token_t* lexer_collect_string(lexer_t* l)
{
	char* s = calloc(1, sizeof(char));
	size_t s_size = 0;

	lexer_advance(l);

	while (l->current_char != '"') 
	{
		s[s_size] = l->current_char;
		s_size += 1;
		s = realloc(s, (s_size + 1) * sizeof(char));

		lexer_advance(l);
	}

	return token_new(STRING, s);
}

token_t* lexer_collect_integer(lexer_t* l)
{
	char* s = calloc(1, sizeof(char));
	size_t s_size = 0;

	while (isdigit(l->current_char)) 
	{
		s[s_size] = l->current_char;
		s_size += 1;
		s = realloc(s, (s_size + 1) * sizeof(char));

		lexer_advance(l);
	}

	return token_new(INTEGER, s);
}
