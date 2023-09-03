#include "include/symbol.h"
#include <stdio.h>
#include <stdlib.h>

symbol_T* init_symbol(symbol_E symbol, char* name)
{
	symbol_T* sym = malloc(sizeof(symbol_T));
	sym->category = symbol;
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

symbol_T* init_proc_symbol(char* name)
{
	proc_symbol_T* proc = malloc(sizeof(proc_symbol_T));
	proc->base = *init_symbol(SYM_PROC, name);
	proc->params = calloc(1, sizeof(var_symbol_T));
	proc->param_count = 0;

	return (symbol_T*) proc;
}


void proc_add_param(proc_symbol_T* proc, var_symbol_T* param)
{
	proc->params[proc->param_count] = param;
	proc->param_count += 1;
	proc->params = realloc(proc->params, (proc->param_count + 1) * sizeof(var_symbol_T));
}

char* symbol_to_string(symbol_T* symbol)
{
	char* s = malloc(100 * sizeof(char));

	switch (symbol->category) 
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

		case SYM_PROC:
			{
				proc_symbol_T* proc = (proc_symbol_T*) symbol;
				sprintf(s, "<%s: procedure, params: %zu>", proc->base.name, proc->param_count);
			}
			break;
	}
	return s;
}
