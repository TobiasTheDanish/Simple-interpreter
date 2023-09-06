#include "include/source_to_source_compiler.h"
#include "include/ast_node.h"
#include "include/sym_table.h"
#include "include/symbol.h"
#include "include/types.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void append_to_output(src_2_src_compiler_T* compiler, char* str)
{
	compiler->output_size += strlen(str);
	compiler->output = realloc(compiler->output, (compiler->output_size + 1) * sizeof(char));
	strcat(compiler->output, str);
}

src_2_src_compiler_T* init_src_to_src_compiler()
{
	src_2_src_compiler_T* compiler = malloc(sizeof(src_2_src_compiler_T));

	compiler->scope = (void*)0;
	compiler->output_size = 10000;
	compiler->output = calloc(compiler->output_size, sizeof(char));

	return compiler;
}

void SRC_visit_program(src_2_src_compiler_T* compiler, ast_node_T* node) 
{
	printf("\nSource to source compiler:\n\n");
	program_node_T* prog = (program_node_T*) node;
	char* prog_name = prog->name;

	char* result_str = malloc(100 * sizeof(char));
	sprintf(result_str, "program %s0\n", prog_name);
	append_to_output(compiler, result_str);

	scoped_sym_table_T* global_scope = init_sym_table("global", 1, (void*)0);
	init_builtin_symbols(global_scope);

	compiler->scope = global_scope;

	SRC_visit(compiler, (ast_node_T*)prog->block);

	result_str = malloc(100 * sizeof(char));
	sprintf(result_str, ". {END OF %s}", prog_name);
	append_to_output(compiler, result_str);
	
	compiler->scope = compiler->scope->enclosing_scope;
}

void SRC_visit_block(src_2_src_compiler_T* compiler, ast_node_T* node)
{
	block_node_T* block = (block_node_T*) node;

	for(int i = 0; i < block->decl_count; i++)
	{
		decl_node_T* current = block->decls[i];

		SRC_visit(compiler, (ast_node_T*)current);
	}

	append_to_output(compiler, "\nbegin");

	SRC_visit(compiler, (ast_node_T*)block->comp);

	append_to_output(compiler, "end");
}

void SRC_visit_procdecl(src_2_src_compiler_T* compiler, ast_node_T* node)
{
	decl_node_T* decl = (decl_node_T*) node;
	procdecl_node_T* proc = decl->node->proc;

	char* proc_name = proc->name;

	proc_symbol_T* proc_sym = (proc_symbol_T*)init_proc_symbol(proc_name);
	sym_table_add(compiler->scope, (symbol_T*)proc_sym);

	char* str = malloc(100*sizeof(char));
	sprintf(str, "procedure %s%hhd", proc_name, compiler->scope->level);
	append_to_output(compiler, str);

	scoped_sym_table_T* proc_scope = init_sym_table(
			proc_name,
			compiler->scope->level + 1,
			compiler->scope->enclosing_scope
			);
	compiler->scope = proc_scope;
	
	if (proc->param_count > 0) 
	{
		append_to_output(compiler, "(");
	}

	for (int i = 0; i < proc->param_count; i++) 
	{
		vardecl_node_T* param = proc->params[i]->vardecl;
		option_T* param_type = sym_table_get(compiler->scope, param->type->val);

		switch (param_type->type) 
		{
			case Value:
				{
					str = malloc(100 * sizeof(char));

					for (int j = 0; j < param->count; j++)
					{
						symbol_T* var_sym = init_var_symbol(param->var[j]->name, param_type->val.val);
						sym_table_add(compiler->scope, var_sym);
						proc_add_param(proc_sym, (var_symbol_T*) var_sym);

						if (j == 0 && i != 0) 
						{
							sprintf(str, "; %s%hdd : %s; ",param->var[j]->name, compiler->scope->level, (char*)param_type->val.val);
						}
						else if (j < param->count-1) 
						{
							sprintf(str, "%s%hdd : %s; ",param->var[j]->name, compiler->scope->level, (char*)param_type->val.val);
						}
						else 
						{
							sprintf(str, "%s%hdd : %s",param->var[j]->name, compiler->scope->level, (char*)param_type->val.val);
						}

						append_to_output(compiler, str);
					}
				}
				break;

			case Err:
				printf("%s\n", param_type->val.err);
				exit(69);
		}
	}

	if (proc->param_count > 0) 
	{
		append_to_output(compiler, ")");
	}
	append_to_output(compiler, ";\n");

	SRC_visit(compiler, proc->block);

	str = malloc(50 * sizeof(char));
	sprintf(str, "; {END OF %s}", proc_name);
	append_to_output(compiler, str);

	compiler->scope = compiler->scope->enclosing_scope;
}

void SRC_visit_vardecl(src_2_src_compiler_T* compiler, ast_node_T* node)
{
	decl_node_T* decl = (decl_node_T*) node;
	vardecl_node_T* var = decl->node->var;
}

void SRC_visit(src_2_src_compiler_T* compiler, ast_node_T* node) 
{
	printf("Visit called on node with type %d\n", node->type);
	switch (node->type) 
	{
		case PROGRAM:
			SRC_visit_program(compiler, node);
			break;

		case BLOCK:
			SRC_visit_block(compiler, node);
			break;

		case VARDECL:
			SRC_visit_vardecl( compiler, node);
			break;

		case PROCDECL:
			SRC_visit_procdecl( compiler, node);
			break;

		default:
			exit(69);
			break;
	}
}
