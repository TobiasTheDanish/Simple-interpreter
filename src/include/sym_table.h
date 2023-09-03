#ifndef SYM_TABLE_H
#define SYM_TABLE_H

#include "symbol.h"
#include "types.h"
#include <stddef.h>
#include <stdint.h>

typedef struct SCOPED_SYMBOL_TABLE_STRUCT
{
	char* name;
	int8_t level;
	symbol_T** symbols;
	size_t size;
} scoped_sym_table_T;

void init_builtin_symbols(scoped_sym_table_T* table);

scoped_sym_table_T* init_sym_table(char* name, int8_t level);

void sym_table_add(scoped_sym_table_T* table, symbol_T* symbol);

option_T* sym_table_get(scoped_sym_table_T* table, char* name);

void sym_table_print(scoped_sym_table_T* table);

void sym_table_free(scoped_sym_table_T* table);

#endif // !SYM_TABLE_H
