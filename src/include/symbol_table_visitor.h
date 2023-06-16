#ifndef SYMBOL_TABLE_VISITOR_H
#define SYMBOL_TABLE_VISITOR_H

#include "ast_node.h"
#include "sym_table.h"
typedef struct SYMBOL_TABLE_VISITOR_STRUCT
{
	sym_table_T* symbols;
} sym_table_visitor_T;

sym_table_visitor_T* init_sym_table_visitor();

void visit(sym_table_visitor_T* visitor, ast_node_T* node);
#endif // !SYMBOL_TABLE_VISITOR_H
