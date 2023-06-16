#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "parser.h"

typedef struct INTERPRETER_STRUCT
{
	parser_T* p;
	struct list_map* global_scope;
} interpreter_T;

interpreter_T* I_init(char* s);

int I_run(interpreter_T* i);

#endif // !INTERPRETER_H
