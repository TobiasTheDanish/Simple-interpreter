#include "include/interpreter.h"
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

interpreter_T* I_init(char* src)
{
	interpreter_T* interpreter = calloc(1, sizeof(interpreter_T));
	interpreter->src = src;
	interpreter->pos = 0;
	interpreter->current_char = interpreter->src[interpreter->pos];
	interpreter->current_token = I_get_next_token(interpreter);

	return interpreter;
}

void advance(interpreter_T* interpreter)
{
	interpreter->pos += 1;
	interpreter->current_char = interpreter->src[interpreter->pos];
}

token_T* advance_with_token(interpreter_T* interpreter, token_T* token)
{
	advance(interpreter);

	return token;
}

void clear_whitespace(interpreter_T* interpreter)
{
	while (interpreter->current_char == ' ' || interpreter->current_char == 10 || interpreter->current_char == 9) {
		advance(interpreter);
	}
}

token_T* I_get_next_token(interpreter_T* interpreter)
{
	clear_whitespace(interpreter);

	if (interpreter->pos >= strlen(interpreter->src)-1)
	{
		return token_init(T_EOF, "\0");
	}

	if (isdigit(interpreter->current_char))
		return I_collect_token(interpreter, V_NUMBER);
	
	switch (interpreter->current_char) {
		case '+':
			return advance_with_token(interpreter, token_init(T_PLUS, char_to_string(interpreter->current_char)));
		case '-':
			return advance_with_token(interpreter, token_init(T_MINUS, char_to_string(interpreter->current_char)));
		case '*':
			return advance_with_token(interpreter, token_init(T_MULTIPLY, char_to_string(interpreter->current_char)));
		case '/':
			return advance_with_token(interpreter, token_init(T_DIVIDE, char_to_string(interpreter->current_char)));
	} 

	return token_init(T_EOF, "\0");
}

token_T* collect_string(interpreter_T* interpreter)
{
	char* val = calloc(1, sizeof(char));
	size_t length = 0;

	while (interpreter->current_char != '"') {
		//printf("%c\n", interpreter->current_char);
		val[length] = interpreter->current_char;
		length += 1;
		val = realloc(val, (length + 1) * sizeof(char));

		advance(interpreter);
	}

	return token_init(T_STRING, val);
}

token_T* collect_number(interpreter_T* interpreter)
{
	char* val = calloc(1, sizeof(char));
	size_t length = 0;

	while (isdigit(interpreter->current_char)) {
		//printf("%c\n", interpreter->current_char);
		val[length] = interpreter->current_char;
		length += 1;
		val = realloc(val, (length + 1) * sizeof(char));

		advance(interpreter);
	}

	return token_init(T_INTEGER, val);
}

token_T* I_collect_token(interpreter_T* interpreter, int type)
{
	switch (type) 
	{
		case V_NUMBER:
			return collect_number(interpreter);

		case V_STRING:
			return collect_string(interpreter);

		default:
			printf("Unexpected value type encountered with type %d\n", type);
			exit(1);
	}
}

void I_eat(interpreter_T* interpreter, int token_type)
{
	if (interpreter->current_token->type == token_type) 
	{
		//printf("%s\n", token_as_string(interpreter->current_token));
		interpreter->current_token = I_get_next_token(interpreter);
	}
	else 
	{
		printf("Unexpected token type, when trying to eat. Expected type: %d found: %d\n", token_type, interpreter->current_token->type);
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

token_T* get_operation(interpreter_T* interpreter)
{
	token_T* operation = interpreter->current_token;

	I_eat(interpreter, operation->type);

	return operation;
}

int I_term(interpreter_T *interpreter)
{
	int result = I_factor(interpreter);
	
	while (token_is_operation(interpreter->current_token) && operation_is_multiplicative(interpreter->current_token)) {
		token_T* op = get_operation(interpreter);

		switch (op->type) {
			case T_MULTIPLY:
				result *= I_factor(interpreter);
				break;

			case T_DIVIDE:
				result /= I_factor(interpreter);
				break;

			default:
				printf("Non implemented operation encountered! Type: %d\n", op->type);
				return 0;
		}
	}

	return result;
}

int I_factor(interpreter_T* interpreter)
{
	int val = atoi(interpreter->current_token->value);

	I_eat(interpreter, T_INTEGER);

	return val;
}

int integer_expr(interpreter_T* interpreter) 
{
	int result = I_term(interpreter);

	while (token_is_operation(interpreter->current_token) && operation_is_additive(interpreter->current_token)) {
		token_T* operation = get_operation(interpreter);

		switch (operation->type) {
			case T_PLUS:
				result = result + I_term(interpreter);
				break;

			case T_MINUS:
				result = result - I_term(interpreter);
				break;

			default:
				printf("Non implemented operation encountered! Type: %d\n", operation->type);
				return 0;
		}
	}

	return result;
}

int I_expr(interpreter_T* interpreter)
{
	switch (interpreter->current_token->type) {
		case T_INTEGER:
			return integer_expr(interpreter);

		default:
			return 0;
	
	}
}
