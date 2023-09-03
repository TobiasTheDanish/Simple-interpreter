#ifndef SYMBOL_H
#define SYMBOL_H

#include <stddef.h>
typedef enum SYMBOL_ENUM
{
	SYM_VAR,
	SYM_PROC,
	SYM_BUILTIN_TYPE,
} symbol_E;

typedef enum BUILTIN_TYPES_ENUM
{
	SYM_INTEGER,
	SYM_REAL,
	SYM_NONE,
} builtin_types_E;

typedef struct SYMBOL_BASE_STRUCT
{
	symbol_E category;
	char* name;
} symbol_T;

typedef struct VAR_SYMBOL_STRUCT
{
	symbol_T base;
	symbol_T* type;
} var_symbol_T;

typedef struct PROC_SYMBOL_STRUCT
{
	symbol_T base;
	var_symbol_T** params;
	size_t param_count;
} proc_symbol_T;

symbol_T* init_symbol(symbol_E symbol, char* name);

symbol_T* init_var_symbol( char* name, symbol_T* type);

symbol_T* init_proc_symbol(char* name);

void proc_add_param(proc_symbol_T* proc, var_symbol_T* param);

char* symbol_to_string(symbol_T* symbol);

#endif // !SYMBOL_H
