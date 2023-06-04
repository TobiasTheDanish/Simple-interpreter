#include "include/parser.h"
#include "include/ast_node.h"
#include "include/token.h"
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* char_to_string(char c)
{
	char* s = malloc(2 * sizeof(char));
	s[0] = c;
	s[1] = '\0';

	return s;
}

parser_T* P_init(char* src)
{
	parser_T* parser = calloc(1, sizeof(parser_T));
	parser->src = src;
	parser->pos = 0;
	parser->current_char = parser->src[parser->pos];
	parser->current_token = P_get_next_token(parser);

	return parser;
}

void advance(parser_T* parser)
{
	parser->pos += 1;
	parser->current_char = parser->src[parser->pos];
}

token_T* advance_with_token(parser_T* parser, token_T* token)
{
	advance(parser);

	return token;
}

void clear_whitespace(parser_T* parser)
{
	while (parser->current_char == ' ' || parser->current_char == 10 || parser->current_char == 9) {
		advance(parser);
	}
}

token_T* P_get_next_token(parser_T* parser)
{
	clear_whitespace(parser);

	if (parser->pos >= strlen(parser->src)-1)
	{
		return token_init(T_EOF, "\0");
	}

	if (isdigit(parser->current_char))
		return P_collect_token(parser, V_NUMBER);
	
	switch (parser->current_char) {
		case '(':
			return advance_with_token(parser, token_init(T_LPAREN, char_to_string(parser->current_char)));
		case ')':
			return advance_with_token(parser, token_init(T_RPAREN, char_to_string(parser->current_char)));
		case '+':
			return advance_with_token(parser, token_init(T_PLUS, char_to_string(parser->current_char)));
		case '-':
			return advance_with_token(parser, token_init(T_MINUS, char_to_string(parser->current_char)));
		case '*':
			return advance_with_token(parser, token_init(T_MULTIPLY, char_to_string(parser->current_char)));
		case '/':
			return advance_with_token(parser, token_init(T_DIVIDE, char_to_string(parser->current_char)));
	} 

	return token_init(T_EOF, "\0");
}

token_T* collect_string(parser_T* parser)
{
	char* val = calloc(1, sizeof(char));
	size_t length = 0;

	while (parser->current_char != '"') {
		//printf("%c\n", parser->current_char);
		val[length] = parser->current_char;
		length += 1;
		val = realloc(val, (length + 1) * sizeof(char));

		advance(parser);
	}

	return token_init(T_STRING, val);
}

token_T* collect_number(parser_T* parser)
{
	char* val = calloc(1, sizeof(char));
	size_t length = 0;

	while (isdigit(parser->current_char)) {
		//printf("%c\n", parser->current_char);
		val[length] = parser->current_char;
		length += 1;
		val = realloc(val, (length + 1) * sizeof(char));

		advance(parser);
	}

	return token_init(T_INTEGER, val);
}

token_T* P_collect_token(parser_T* parser, int type)
{
	switch (type) 
	{
		case V_NUMBER:
			return collect_number(parser);

		case V_STRING:
			return collect_string(parser);

		default:
			printf("Unexpected value type encountered with type %d\n", type);
			exit(1);
	}
}

void P_eat(parser_T* parser, int token_type)
{
	if (parser->current_token->type == token_type) 
	{
		//printf("%s\n", token_as_string(parser->current_token));
		parser->current_token = P_get_next_token(parser);
	}
	else 
	{
		printf("Unexpected token type, when trying to eat. Expected type: %d found: %d\n", token_type, parser->current_token->type);
	}
}

unsigned char token_is_operation(token_T* token)
{
	unsigned char is_plus = token->type == T_PLUS;
	unsigned char is_minus = token->type == T_MINUS;
	unsigned char is_multiply = token->type == T_MULTIPLY;
	unsigned char is_divide = token->type == T_DIVIDE;

	return is_plus || is_minus || is_multiply || is_divide;
}

unsigned char operation_is_additive(token_T* token)
{
	unsigned char is_plus = token->type == T_PLUS;
	unsigned char is_minus = token->type == T_MINUS;

	return is_plus || is_minus;
}

unsigned char operation_is_multiplicative(token_T* token)
{
	unsigned char is_multiply = token->type == T_MULTIPLY;
	unsigned char is_divide = token->type == T_DIVIDE;

	return is_multiply || is_divide;
}

token_T* get_operation(parser_T* parser)
{
	token_T* operation = parser->current_token;

	P_eat(parser, operation->type);

	return operation;
}

ast_node_T* get_int_node(parser_T* parser)
{
	ast_node_T* node = init_num(parser->current_token);

	P_eat(parser, T_INTEGER);

	return node;
}

ast_node_T* P_factor(parser_T* parser)
{
	switch (parser->current_token->type)
	{
		case T_LPAREN:
			P_eat(parser, T_LPAREN);
			ast_node_T* node = P_expr(parser);
			P_eat(parser, T_RPAREN);
			return node;

		case T_INTEGER:
			return get_int_node(parser);

		default:
			printf("Unexpected token type, in P_factor. Type: %d\n", parser->current_token->type);
			return 0;
	}
}

ast_node_T* P_term(parser_T *parser)
{
	ast_node_T* left = P_factor(parser);

	while (token_is_operation(parser->current_token) && operation_is_multiplicative(parser->current_token)) 
	{
		token_T* op = get_operation(parser);

		left = init_bin_op(op, left, P_term(parser));
	}

	return left;
}

ast_node_T* P_expr(parser_T* parser)
{
	ast_node_T* left = P_term(parser);

	while (token_is_operation(parser->current_token) && operation_is_additive(parser->current_token)) 
	{
		token_T* op = get_operation(parser);

		left = init_bin_op(op, left, P_term(parser));
	}

	return left;
}

ast_node_T* P_parse(parser_T* parser)
{
	return P_expr(parser);
}
