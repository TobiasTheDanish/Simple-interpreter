#include "include/ast_node.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
ast_node_T* init_program(char* name, ast_node_T* block)
{
	ast_node_T* ast = malloc(sizeof(ast_node_T));
	ast->type = PROGRAM;

	program_node_T* program = malloc(sizeof(program_node_T));
	program->ast = *ast;
	program->name = name;
	program->block = (block_node_T*) block;

	return (ast_node_T*) program;
}

ast_node_T* init_block(decl_node_T** decls, size_t count, ast_node_T* comp)
{
	ast_node_T* ast = malloc(sizeof(ast_node_T));
	ast->type = BLOCK;

	block_node_T* block = malloc(sizeof(block_node_T));
	block->ast = *ast;
	block->decls = decls;
	block->decl_count = count;
	block->comp = (compound_node_T*) comp;

	return (ast_node_T*) block;
}

procdecl_node_T* init_proc_decl(char* name, param_node_T** params, size_t param_count, ast_node_T* block)
{
	procdecl_node_T* decl = malloc(sizeof(procdecl_node_T));
	decl->name = name;
	decl->params = params;
	decl->param_count = param_count;
	decl->block = block;

	return decl;
}

vardecl_node_T* init_var_decl(var_node_T** vars, size_t count, ast_node_T* type)
{
	vardecl_node_T* decl = malloc(sizeof(vardecl_node_T));
	decl->var = vars;
	decl->count = count;
	decl->type = (type_node_T*) type;

	return decl;
}

param_node_T* init_param(vardecl_node_T* vardecl) 
{
	ast_node_T* ast = malloc(sizeof(ast_node_T));
	ast->type = PARAM;

	param_node_T* param = malloc(sizeof(param_node_T));
	param->ast = *ast;
	param->vardecl = vardecl;

	return param;
}

ast_node_T* init_decl(unsigned int type, void* node)
{
	ast_node_T* ast = malloc(sizeof(ast_node_T));
	ast->type = type;

	decl_node_T* decl = malloc(sizeof(decl_node_T));
	decl->ast = *ast;
	decl->node = malloc(sizeof(decl_node_U));

	switch (type) 
	{
		case VARDECL:
			decl->node->var = node;
			break;
	
		case PROCDECL:
			decl->node->proc = node;
			break;

		default:
			printf("Unimplemented declaration with type %d\n", type);
			exit(1);
	}

	return (ast_node_T*) decl;
}

ast_node_T* init_type(token_T* t)
{
	ast_node_T* ast = malloc(sizeof(ast_node_T));
	ast->type = TYPE_SPEC;

	type_node_T* type = malloc(sizeof(type_node_T));
	type->ast = *ast;
	type->token = t;
	type->val = t->value;

	return (ast_node_T*) type;
}

ast_node_T* init_comp()
{
	ast_node_T* ast = malloc(sizeof(ast_node_T));
	ast->type = COMPOUND;

	compound_node_T* comp = calloc(1, sizeof(compound_node_T));
	comp->ast = *ast;
	comp->children = calloc(1, sizeof(ast_node_T*));
	comp->child_count = 0;

	return (ast_node_T*) comp;
}

ast_node_T* init_assign(token_T* t, var_node_T* l_child, ast_node_T* r_child)
{
	ast_node_T* ast = malloc(sizeof(ast_node_T));
	ast->type = ASSIGN;

	assign_node_T* a = malloc(sizeof(assign_node_T));
	a->ast = *ast;
	a->t = t;
	a->left_child = l_child;
	a->right_child = r_child;

	return (ast_node_T*) a;
}

var_node_T* init_var(token_T* t)
{
	ast_node_T* ast = malloc(sizeof(ast_node_T));
	ast->type = VAR;

	var_node_T* var = malloc(sizeof(var_node_T));
	var->ast = *ast;
	var->t = t;
	var->name = t->value;

	return var;
}

ast_node_T* init_bin_op(token_T* t, ast_node_T* l_child, ast_node_T* r_child)
{
	ast_node_T* ast = malloc(sizeof(ast_node_T));
	ast->type = BIN_OP;

	bin_op_node_T* op = malloc(sizeof(bin_op_node_T));
	op->ast = *ast;
	op->t = t;
	op->left_child = l_child;
	op->right_child = r_child;

	return (ast_node_T*) op;
}

ast_node_T* init_num(token_T* t)
{
	ast_node_T* ast = malloc(sizeof(ast_node_T));
	ast->type = NUM;

	num_node_T* num = malloc(sizeof(num_node_T));
	num->ast = *ast;
	num->t = t;
	switch (t->type) {
		case T_INT_CONST:
			num->val = (num_T) {.type = INTEGER, .value = (num_U) {.i = atoi(t->value)}};
			break;
	
		case T_REAL_CONST:
			num->val = (num_T) {.type = FLOAT, .value = (num_U) {.f = atof(t->value)}};
			break;

		default:
			printf("[init_num]: Token type %d is not a valid num type\n", t->type);
			exit(1);
	}

	return (ast_node_T*) num;
}

ast_node_T* init_unary_op(token_T* t, ast_node_T* expr)
{
	ast_node_T* ast = malloc(sizeof(ast_node_T));
	ast->type = UNARY_OP;

	unary_op_node_T* op = malloc(sizeof(unary_op_node_T));
	op->ast = *ast;
	op->t = t;
	op->expr = expr;

	return (ast_node_T*) op;
}

ast_node_T* init_noop()
{
	ast_node_T* ast = malloc(sizeof(ast_node_T));
	ast->type = NOOP;

	return ast;
}
