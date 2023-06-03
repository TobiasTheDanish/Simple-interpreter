#include "include/interpreter.h"
#include "include/lexer.h"
#include "include/token.h"
#include <stdio.h>
#include <stdlib.h>

interpreter_t* interpreter_new(lexer_t* l)
{
	interpreter_t* i = malloc(sizeof(interpreter_t));
	i->lexer = l;
	i->current_token = lexer_get_next_token(l);

	return i;
}

void interpreter_eat(interpreter_t* i, unsigned int t_type)
{
	if (i->current_token->type == t_type)
	{
		i->current_token = lexer_get_next_token(i->lexer);
	}
	else 
	{
		//printf("Unexpected token when trying to eat, found: %d, expected: %d\n", i->current_token->type, t_type);
		exit(1);
	}
}

_Bool operation_is_additive(token_t* t)
{
	_Bool is_plus = t->type == PLUS;
	_Bool is_minus = t->type == MINUS;

	return is_plus || is_minus;
}

_Bool operation_is_multiplicative(token_t* t)
{
	_Bool is_multiply = t->type == MULTIPLY;
	_Bool is_divide = t->type == DIVIDE;

	return is_divide || is_multiply;
}

_Bool token_is_operation(token_t* t)
{
	_Bool is_plus = t->type == PLUS;
	_Bool is_minus = t->type == MINUS;
	_Bool is_multiply = t->type == MULTIPLY;
	_Bool is_divide = t->type == DIVIDE;

	return is_plus || is_minus || is_multiply || is_divide;
}

int interpreter_factor(interpreter_t* i)
{
	int result = 0;
	//printf("FACTOR: next token, (type: %d, val: %s)\n", i->current_token->type, i->current_token->value);

	if (i->current_token->type == LPAREN)
	{
		interpreter_eat(i, LPAREN);
		result = interpreter_expr(i);
		interpreter_eat(i, RPAREN);
	}
	else 
	{
		result = atoi(i->current_token->value);
		interpreter_eat(i, INTEGER);
	}

	return result;
}

int interpreter_term(interpreter_t* i)
{
	int result = interpreter_factor(i);
	//printf("TERM: result = %d\n", result);

	while (token_is_operation(i->current_token) && operation_is_multiplicative(i->current_token)) 
	{
		token_t* op = i->current_token;
		//printf("TERM: operation, (type: %d, val: %s\n)", op->type, op->value);

		switch (op->type) 
		{
			case MULTIPLY:
				interpreter_eat(i, MULTIPLY);
				result = result * interpreter_factor(i);
				//printf("TERM: after multiply, result = %d\n", result);
				break;

			case DIVIDE:
				interpreter_eat(i, DIVIDE);
				result = result / interpreter_factor(i);
				//printf("TERM: after divide, result = %d\n", result);
				break;

			default:
				return result;
		}
	}

	return result;
}

int interpreter_expr(interpreter_t* i)
{
	int result = interpreter_term(i);

	while (token_is_operation(i->current_token) && operation_is_additive(i->current_token)) 
	{
		token_t* op = i->current_token;
		//printf("EXPR: operation, (type: %d, val: %s\n)", op->type, op->value);

		switch (op->type) 
		{
			case PLUS:
				interpreter_eat(i, PLUS);
				result = result + interpreter_term(i);
				break;

			case MINUS:
				interpreter_eat(i, MINUS);
				result = result - interpreter_term(i);
				break;

			default:
				return result;
		}
	}

	return result;
}
