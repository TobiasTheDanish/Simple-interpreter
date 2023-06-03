#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "lexer.h"
#include "token.h"

typedef struct INTERPRETER_S
{
	lexer_t* lexer;
	token_t* current_token;
} interpreter_t;

interpreter_t* interpreter_new(lexer_t* l);

void interpreter_eat(interpreter_t* i, unsigned int t_type);

int interpreter_term(interpreter_t* i);

int interpreter_factor(interpreter_t* i);

int interpreter_expr(interpreter_t* i);

#endif // !INTERPRETER_H
