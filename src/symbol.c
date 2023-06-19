#include "include/symbol.h"
#include <stdio.h>
#include <stdlib.h>

symbol_T* init_symbol(symbol_E symbol, char* name)
{
	symbol_T* sym = malloc(sizeof(symbol_T));
	sym->symbol = symbol;
	sym->name = name;

	return sym;
}

symbol_T* init_var_symbol( char* name, symbol_T* type)
{
	var_symbol_T* var = malloc(sizeof(var_symbol_T));
	var->base = *init_symbol(SYM_VAR, name);
	var->type = type;

	return (symbol_T*) var;
}

char* symbol_to_string(symbol_T* symbol)
{
	char* s = malloc(sizeof(char));

	switch (symbol->symbol) 
	{
		case SYM_BUILTIN_TYPE:
			sprintf(s, "%s", symbol->name);
			break;

		case SYM_VAR:
			{
				var_symbol_T* var = (var_symbol_T*) symbol;
				sprintf(s, "<%s:%s>", var->base.name, var->type->name);
			}
			break;
	}
	return s;
}
