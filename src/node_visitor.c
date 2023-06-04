#include "include/node_visitor.h"
#include "include/ast_node.h"
#include "include/token.h"
#include <stdio.h>
#include <stdlib.h>

int visit_bin_op(ast_node_T* node)
{
	bin_op_node_T* bin = (bin_op_node_T*) node;
	switch (bin->t->type) 
	{
		case T_PLUS:
			return visit(bin->left_child) + visit(bin->right_child);

		case T_MINUS:
			return visit(bin->left_child) - visit(bin->right_child);

		case T_MULTIPLY:
			return visit(bin->left_child) * visit(bin->right_child);

		case T_DIVIDE:
			return visit(bin->left_child) / visit(bin->right_child);

		default:
			printf("Non implemented operation for bin_op node: (type: %d, val: %s)\n", bin->t->type, bin->t->value);
			exit(1);
	}
}

int visit_num(ast_node_T* node)
{
	num_node_T* num = (num_node_T*) node;

	return num->val;
}

int visit(ast_node_T* node)
{
	switch (node->type) 
	{
		case BIN_OP:
			return visit_bin_op(node);

		case NUM:
			return visit_num(node);
	}
}
