#include "include/node_visitor.h"
#include "include/ast_node.h"
#include "include/list_map.h"
#include "include/token.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void visit_compound(interpreter_T* i, ast_node_T* node)
{
	compound_node_T* comp = (compound_node_T*) node;

	for (size_t index = 0; index < comp->child_count; index++)
	{
		visit(i, comp->children[index]);
	}
}

void visit_assign(interpreter_T* i, ast_node_T* node)
{
	assign_node_T* assign = (assign_node_T*) node;

	printf("[visit_assign] Var name: %s, val type: %d\n", assign->left_child->name, assign->right_child->type);
	if (!list_map_insert(i->global_scope, assign->left_child->name, visit(i, assign->right_child))) 
	{
		printf("[visit_assign] Failed to insert var to global_scope");
	}
}

int visit_var(interpreter_T* i, ast_node_T* node)
{
	var_node_T* var = (var_node_T*) node;

	option_T opt = list_map_get(i->global_scope, var->name);

	switch (opt.type) 
	{
		case Value:
			printf("[visit_var] var name: %s, var val:%d\n", var->name, opt.val.val);
			return opt.val.val;

		case Err:
			perror(opt.val.err);
			return 0;
	}
}

void visit_noop(interpreter_T* i, ast_node_T* node)
{
}

int visit_unary_op(interpreter_T* i, ast_node_T* node)
{
	unary_op_node_T* op = (unary_op_node_T*) node;
	printf("[visit_unary_op] expr: %d\n", op->expr->type);

	switch (op->t->type) {
		case T_PLUS:
			return +visit(i, op->expr);

		case T_MINUS:
			return -visit(i, op->expr);

		default:
			printf("Non implemented operation for unary_op node: (type: %d, val: %s)\n", op->t->type, op->t->value);
			exit(1);
	}
}

int visit_num(interpreter_T* i, ast_node_T* node)
{
	num_node_T* num = (num_node_T*) node;
	printf("[visit_num] num->val: %d\n", num->val);

	return num->val;
}

int visit_bin_op(interpreter_T* i, ast_node_T* node)
{
	bin_op_node_T* bin = (bin_op_node_T*) node;
	printf("[visit_bin_op] bin left_child: %d, op: %s bin right_child: %d\n", bin->left_child->type, token_as_string(bin->t), bin->right_child->type);
	int left = 0;
	int right = 0;
	
	switch (bin->t->type) 
	{
		case T_PLUS:
			left = visit(i, bin->left_child);
			right = visit(i, bin->right_child);
			printf("%d + %d\n", left, right);
			return left + right;

		case T_MINUS:
			left = visit(i, bin->left_child);
			right = visit(i, bin->right_child);
			printf("%d - %d\n", left, right);
			return left - right;

		case T_MULTIPLY:
			left = visit(i, bin->left_child);
			right = visit(i, bin->right_child);
			printf("%d * %d\n", left, right);
			return left * right;

		case T_DIVIDE:
			left = visit(i, bin->left_child);
			right = visit(i, bin->right_child);
			printf("%d / %d\n", left, right);
			return left / right;

		default:
			printf("Non implemented operation for bin_op node: (type: %d, val: %s)\n", bin->t->type, bin->t->value);
			exit(1);
	}
}

int visit(interpreter_T* i, ast_node_T* node)
{
	//printf("Visit called on node with type %d\n", node->type);
	switch (node->type) 
	{
		case COMPOUND:
			visit_compound(i, node);
			break;

		case ASSIGN:
			visit_assign(i, node);
			break;

		case VAR:
			return visit_var(i, node);

		case BIN_OP:
			return visit_bin_op(i, node);

		case NUM:
			return visit_num(i, node);

		case UNARY_OP:
			return visit_unary_op(i, node);

		case NOOP:
			visit_noop(i, node);
			break;
	}

	return 0;
}
