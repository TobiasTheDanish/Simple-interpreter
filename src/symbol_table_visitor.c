#include "include/symbol_table_visitor.h"
#include "include/ast_node.h"
#include "include/sym_table.h"
#include "include/symbol.h"
#include "include/types.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

sym_table_visitor_T* init_sym_table_visitor()
{
	sym_table_visitor_T* visitor = malloc(sizeof(sym_table_visitor_T));
	visitor->symbols = init_sym_table();

	return visitor;
}

void visit_program(sym_table_visitor_T* visitor, ast_node_T* node)
{
	program_node_T* prog = (program_node_T*) node;

	visit(visitor, (ast_node_T*) prog->block);
}

void visit_block(sym_table_visitor_T* visitor, ast_node_T* node)
{
	block_node_T* block = (block_node_T*) node;

	for (size_t i = 0; i < block->decl_count; i++) 
	{
		visit(visitor, (ast_node_T*) block->decls[i]);
	}

	visit(visitor, (ast_node_T*) block->comp);
}

void visit_vardecl(sym_table_visitor_T* visitor, ast_node_T* node)
{
	vardecl_node_T* decl = (vardecl_node_T*) node;

	option_T option = sym_table_get(visitor->symbols, decl->type->val);

	switch (option.type) 
	{
		case Value:
			{
				symbol_T* type_sym = option.val.val;

				for (size_t i = 0; i < decl->count; i++)
				{
					char* name = decl->var[i]->name;
					sym_table_add(visitor->symbols, init_var_symbol(name, type_sym));
				}
			}
			break;

		case Err:
			printf("%s\n", option.val.err);
			break;
	}
}

void visit_compound(sym_table_visitor_T* visitor, ast_node_T* node)
{
	compound_node_T* comp = (compound_node_T*) node;

	for (size_t i = 0; i < comp->child_count; i++)
	{
		visit(visitor, comp->children[i]);
	}
}

void visit_bin_op(sym_table_visitor_T* visitor, ast_node_T* node)
{
	bin_op_node_T* bin = (bin_op_node_T*) node;

	visit(visitor, bin->left_child);
	visit(visitor, bin->right_child);
}

void visit_unary_op(sym_table_visitor_T* visitor, ast_node_T* node)
{
	unary_op_node_T* unary = (unary_op_node_T*) node;

	visit(visitor, unary->expr);
}

void visit_num(sym_table_visitor_T* visitor, ast_node_T* node)
{}

void visit_noop(sym_table_visitor_T* visitor, ast_node_T* node)
{}

void visit(sym_table_visitor_T* visitor, ast_node_T* node)
{
	switch (node->type) 
	{
		case PROGRAM:
			visit_program(visitor, node);
			break;

		case BLOCK:
			visit_block(visitor, node);
			break;

		case VARDECL:
			visit_vardecl(visitor, node);

		case COMPOUND:
			visit_compound(visitor, node);
			break;

		case BIN_OP:
			visit_bin_op(visitor, node);
			break;

		case UNARY_OP:
			visit_unary_op(visitor, node);
			break;

		case NUM:
			visit_num(visitor, node);
			break;

		case NOOP:
			visit_noop(visitor, node);
			break;
	}
}
