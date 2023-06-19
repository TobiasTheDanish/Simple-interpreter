#ifndef SYMBOL_H
#define SYMBOL_H

typedef enum SYMBOL_ENUM
{
	SYM_VAR,
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
	symbol_E symbol;
	char* name;
} symbol_T;

typedef struct VAR_SYMBOL_STRUCT
{
	symbol_T base;
	symbol_T* type;
} var_symbol_T;


symbol_T* init_symbol(symbol_E symbol, char* name);

symbol_T* init_var_symbol( char* name, symbol_T* type);

char* symbol_to_string(symbol_T* symbol);

#endif // !SYMBOL_H
