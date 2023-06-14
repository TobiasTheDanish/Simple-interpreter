#include "include/ast_node.h"
#include <stddef.h>
#include <stdlib.h>

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
	num->val = atoi(t->value);

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
