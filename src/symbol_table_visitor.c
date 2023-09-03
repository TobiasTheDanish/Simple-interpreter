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

void S_visit_program(sym_table_visitor_T* visitor, ast_node_T* node)
{
	program_node_T* prog = (program_node_T*) node;

	S_visit(visitor, (ast_node_T*) prog->block);
}

void S_visit_block(sym_table_visitor_T* visitor, ast_node_T* node)
{
	block_node_T* block = (block_node_T*) node;

	for (size_t i = 0; i < block->decl_count; i++) 
	{
		S_visit(visitor, (ast_node_T*) block->decls[i]);
	}

	S_visit(visitor, (ast_node_T*) block->comp);
}

void S_visit_vardecl(sym_table_visitor_T* visitor, ast_node_T* node)
{
	decl_node_T* decl = (decl_node_T*) node;
	vardecl_node_T* var = decl->node->var;

	option_T* option = sym_table_get(visitor->symbols, var->type->val);

	switch (option->type) 
	{
		case Value:
			{
				symbol_T* type_sym = option->val.val;

				//printf("[S_visit_vardecl] Adding %zu var declarations with type: %s\n", var->count, type_sym->name);

				for (size_t i = 0; i < var->count; i++)
				{
					//printf("[S_visit_vardecl] i:%zu\n", i);
					char* name = var->var[i]->name;
					option_T* var = sym_table_get(visitor->symbols, name);

					if (var->type == Value) {
						printf("[ERROR]: Variable redeclaration. '%s' already exists.\n", name);
						exit(1);
					}
					
					sym_table_add(visitor->symbols, init_var_symbol(name, type_sym));
				}
			}
			break;

		case Err:
			printf("%s\n", option->val.err);
			break;
	}
}

void S_visit_procdecl(sym_table_visitor_T* visitor, ast_node_T* node)
{
	decl_node_T* decl = (decl_node_T*) node;
	procdecl_node_T* proc = decl->node->proc;

	printf("\n[S_visit_procdecl]: Procedure named '%s' start\n", proc->name);

	S_visit(visitor, proc->block);

	printf("[S_visit_procdecl]: Procedure '%s' end\n\n", proc->name);
}

void S_visit_assign(sym_table_visitor_T* visitor, ast_node_T* node)
{
	assign_node_T* assign = (assign_node_T*) node;

	char* sym_name = assign->left_child->name;

	option_T* opt = sym_table_get(visitor->symbols, sym_name);

	switch (opt->type) 
	{
		case Value:
			S_visit(visitor, assign->right_child);
			break;

		case Err:
			printf("[ERROR S_visit_assign(): Assigning value to variable '%s']: %s", sym_name, opt->val.err);
			exit(1);
	}
}

void S_visit_var(sym_table_visitor_T* visitor, ast_node_T* node)
{
	var_node_T* var = (var_node_T*) node;

	char* sym_name = var->name;

	option_T* opt = sym_table_get(visitor->symbols, sym_name);

	switch (opt->type) 
	{
		case Value:
			break;

		case Err:
			printf("[ERROR S_visit_var()]: %s", opt->val.err);
			exit(1);
	}
}

void S_visit_compound(sym_table_visitor_T* visitor, ast_node_T* node)
{
	compound_node_T* comp = (compound_node_T*) node;

	for (size_t i = 0; i < comp->child_count; i++)
	{
		S_visit(visitor, comp->children[i]);
	}
}

void S_visit_bin_op(sym_table_visitor_T* visitor, ast_node_T* node)
{
	bin_op_node_T* bin = (bin_op_node_T*) node;

	S_visit(visitor, bin->left_child);
	S_visit(visitor, bin->right_child);
}

void S_visit_unary_op(sym_table_visitor_T* visitor, ast_node_T* node)
{
	unary_op_node_T* unary = (unary_op_node_T*) node;

	S_visit(visitor, unary->expr);
}

void S_visit_type_spec(sym_table_visitor_T* visitor, ast_node_T* node)
{}

void S_visit_num(sym_table_visitor_T* visitor, ast_node_T* node)
{}

void S_visit_noop(sym_table_visitor_T* visitor, ast_node_T* node)
{}

void S_visit(sym_table_visitor_T* visitor, ast_node_T* node)
{
	//printf("[S_visit]: Node type: %d\n", node->type);
	switch (node->type) 
	{
		case PROGRAM:
			S_visit_program(visitor, node);
			break;

		case BLOCK:
			S_visit_block(visitor, node);
			break;

		case VARDECL:
			S_visit_vardecl(visitor, node);
			break;

		case PROCDECL:
			S_visit_procdecl(visitor, node);
			break;

		case COMPOUND:
			S_visit_compound(visitor, node);
			break;

		case ASSIGN:
			S_visit_assign(visitor, node);
			break;

		case VAR:
			S_visit_var(visitor, node);
			break;

		case TYPE_SPEC:
			S_visit_type_spec(visitor, node);
			break;

		case BIN_OP:
			S_visit_bin_op(visitor, node);
			break;

		case UNARY_OP:
			S_visit_unary_op(visitor, node);
			break;

		case NUM:
			S_visit_num(visitor, node);
			break;

		case NOOP:
			S_visit_noop(visitor, node);
			break;
	}
}
