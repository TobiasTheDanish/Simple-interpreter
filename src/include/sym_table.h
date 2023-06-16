#ifndef SYM_TABLE_H
#define SYM_TABLE_H

#include "symbol.h"
#include "types.h"
#include <stddef.h>

typedef struct SYMBOL_TABLE_STRUCT
{
	symbol_T** symbols;
	size_t size;
} sym_table_T;

sym_table_T* init_sym_table();

void sym_table_add(sym_table_T* table, symbol_T* symbol);

option_T sym_table_get(sym_table_T* table, char* name);

void sym_table_free(sym_table_T* table);

#endif // !SYM_TABLE_H
