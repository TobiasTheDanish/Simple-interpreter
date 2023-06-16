#include "include/sym_table.h"
#include "include/symbol.h"
#include "include/types.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_builtin_symbols(sym_table_T* table)
{
	sym_table_add(table, init_symbol(BUILTIN_TYPE, "INTEGER", SYM_NONE));
	sym_table_add(table, init_symbol(BUILTIN_TYPE, "REAL", SYM_NONE));
}

sym_table_T* init_sym_table()
{
	sym_table_T* table = malloc(sizeof(sym_table_T));

	table->size = 0;
	table->symbols = malloc(sizeof(symbol_T*));

	init_builtin_symbols(table);

	return table;
}

void sym_table_add(sym_table_T* table, symbol_T* symbol)
{
	table->symbols[table->size] = symbol;
	table->size += 1;

	table->symbols = realloc(table->symbols, (table->size + 1) * sizeof(symbol_T*));
}

option_T sym_table_get(sym_table_T* table, char* name)
{
	option_T option;

	for (size_t i = 0; i < table->size; i++)
	{
		if (strcmp(table->symbols[i]->name, name) == 0) 
		{
			option.type = Value;
			option.val.val = table->symbols[i];
		}
	}

	option.type = Err;
	sprintf(option.val.err, "Unable to lookup symbol: '%s'.\n", name);
	return option;
}

void sym_table_free(sym_table_T* table)
{
	for (size_t i = 0; i < table->size; i++)
	{
		free(table->symbols[i]);
	}

	free(table);
}
