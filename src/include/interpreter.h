#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "token.h"

#include <stddef.h>
enum values
{
	V_STRING,
	V_NUMBER
};

typedef struct INTERPRETER_STRUCT
{
	char current_char;
	char* src;
	size_t pos;
	token_T* current_token;
} interpreter_T;

interpreter_T* I_init(char* src);

token_T* I_get_next_token(interpreter_T* interpreter);

token_T* I_collect_token(interpreter_T* interpreter, int type);

void I_eat(interpreter_T* interpreter, int token_type);

int I_factor(interpreter_T* interpreter);

int I_term(interpreter_T* interpreter);

int I_expr(interpreter_T* interpreter);
#endif // !INTERPRETER_H
