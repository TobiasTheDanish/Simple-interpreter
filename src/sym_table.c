#include "include/sym_table.h"
#include "include/symbol.h"
#include "include/types.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_builtin_symbols(scoped_sym_table_T* table)
{
	sym_table_add(table, init_symbol(SYM_BUILTIN_TYPE, "INTEGER"));
	sym_table_add(table, init_symbol(SYM_BUILTIN_TYPE, "REAL"));
}

scoped_sym_table_T* init_sym_table(char* name, int8_t level)
{
	scoped_sym_table_T* table = malloc(sizeof(scoped_sym_table_T));

	table->name = name;
	table->level = level;
	table->size = 0;
	table->symbols = malloc(sizeof(symbol_T*));

	init_builtin_symbols(table);

	return table;
}

void sym_table_add(scoped_sym_table_T* table, symbol_T* symbol)
{
	table->symbols[table->size] = symbol;
	table->size += 1;

	table->symbols = realloc(table->symbols, (table->size + 1) * sizeof(symbol_T*));

	printf("Added symbol '%s'\n", symbol->name);
}

option_T* sym_table_get(scoped_sym_table_T* table, char* name)
{
	printf("Lookup: %s\n", name);  
	option_T* option = calloc(1, sizeof(option_T));

	for (size_t i = 0; i < table->size; i++)
	{
		if (strcmp(table->symbols[i]->name, name) == 0) {
			option->type = Value;
			option->val.val = table->symbols[i];
			return option;
		}
	}

	option->val.err = malloc(100 * sizeof(char));
	option->type = Err;
	sprintf(option->val.err, "Attempt to access undeclared symbol: '%s'\n", name);
	return option;
}

void sym_table_print(scoped_sym_table_T* table)
{
	printf("\nScope '%s', level %d\n", table->name, table->level);
	for (size_t i = 0; i < table->size; i++)
	{
		printf("\tSymbol #%lu: %s\n", (i+1), symbol_to_string(table->symbols[i]));
	}
}

void sym_table_free(scoped_sym_table_T* table)
{
	for (size_t i = 0; i < table->size; i++)
	{
		free(table->symbols[i]);
	}

	free(table);
}
