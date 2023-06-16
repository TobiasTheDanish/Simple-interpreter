#include "include/symbol.h"
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
	var->base = *init_symbol(VAR, name);
	var->type = type;

	return (symbol_T*) var;
}
