#include "include/ast_node.h"
#include <stdlib.h>

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
