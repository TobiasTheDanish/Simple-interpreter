#include "include/node_visitor.h"
#include "include/ast_node.h"
#include "include/interpreter.h"
#include "include/list_map.h"
#include "include/token.h"
#include "include/types.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void visit_program(interpreter_T* i, ast_node_T* node)
{
	program_node_T* prog = (program_node_T*) node;
	N_visit(i, (ast_node_T*) prog->block);
}

void visit_block(interpreter_T* i, ast_node_T* node)
{
	block_node_T* block = (block_node_T*) node;
	for (size_t index = 0; index < block->decl_count; index++)
	{
		N_visit(i, (ast_node_T*) block->decls[index]);
	}

	N_visit(i, (ast_node_T*) block->comp);
}

void visit_vardecl(interpreter_T* i, ast_node_T* node)
{
}

void visit_type(interpreter_T* i, ast_node_T* node)
{
}

void visit_compound(interpreter_T* i, ast_node_T* node)
{
	compound_node_T* comp = (compound_node_T*) node;

	for (size_t index = 0; index < comp->child_count; index++)
	{
		N_visit(i, comp->children[index]);
	}
}

void visit_assign(interpreter_T* i, ast_node_T* node)
{
	assign_node_T* assign = (assign_node_T*) node;

	printf("\n[visit_assign] Var name: %s, val type: %d\n", assign->left_child->name, assign->right_child->type);
	if (!list_map_insert(i->global_scope, assign->left_child->name, N_visit(i, assign->right_child))) 
	{
		printf("\n[visit_assign] Failed to insert var to global_scope");
	}
}

num_T visit_var(interpreter_T* i, ast_node_T* node)
{
	var_node_T* var = (var_node_T*) node;

	option_T* opt = list_map_get(i->global_scope, var->name);
	num_T val;
	switch (opt->type) 
	{
		case Value:
			val = *(num_T*) opt->val.val;
			if (val.type == INTEGER) 
				printf("[visit_var] var name: %s, var val:%d\n", var->name, val.value.i);
			else 
				printf("[visit_var] var name: %s, var val:%f\n", var->name, val.value.f);
			return val;

		case Err:
			printf("[ERROR]: %s\n", opt->val.err);
			list_map_free(i->global_scope);
			free(i);
			exit(1);
	}
}

void visit_noop(interpreter_T* i, ast_node_T* node)
{
}

num_T visit_unary_op(interpreter_T* i, ast_node_T* node)
{
	unary_op_node_T* op = (unary_op_node_T*) node;
	printf("[visit_unary_op] expr: %d\n", op->expr->type);

	num_T num;

	switch (op->t->type) {
		case T_PLUS:
			num = N_visit(i, op->expr);
			if (num.type == INTEGER)
			{
				num.value.i = +num.value.i;
				return num;
			} 
			else 
			{
				num.value.f = +num.value.f;
				return num;
			}

		case T_MINUS:
			num = N_visit(i, op->expr);
			if (num.type == INTEGER)
			{
				num.value.i = -num.value.i;
				return num;
			} 
			else 
			{
				num.value.f = -num.value.f;
				return num;
			}

		default:
			printf("Non implemented operation for unary_op node: (type: %d, val: %s)\n", op->t->type, op->t->value);
			exit(1);
	}
}

num_T visit_num(interpreter_T* i, ast_node_T* node)
{
	num_node_T* num = (num_node_T*) node;
	printf("[visit_num] num->val: %s\n", num_t_to_string(&num->val));

	return num->val;
}

num_T visit_bin_op(interpreter_T* i, ast_node_T* node)
{
	bin_op_node_T* bin = (bin_op_node_T*) node;
	printf("[visit_bin_op] bin left_child: %d, op: %s bin right_child: %d\n", bin->left_child->type, token_as_string(bin->t), bin->right_child->type);
	num_T left;
	num_T right;
	
	switch (bin->t->type) 
	{
		case T_PLUS:
			left = N_visit(i, bin->left_child);
			right = N_visit(i, bin->right_child);
			printf("%s + %s\n", num_t_to_string(&left), num_t_to_string(&right));
			return num_t_add(left, right);

		case T_MINUS:
			left = N_visit(i, bin->left_child);
			right = N_visit(i, bin->right_child);
			printf("%s - %s\n", num_t_to_string(&left), num_t_to_string(&right));
			return num_t_subtract(left, right);

		case T_MULTIPLY:
			left = N_visit(i, bin->left_child);
			right = N_visit(i, bin->right_child);
			printf("%s * %s\n", num_t_to_string(&left), num_t_to_string(&right));
			return num_t_multiply(left, right);

		case T_INT_DIV:
			left = N_visit(i, bin->left_child);
			right = N_visit(i, bin->right_child);
			printf("%s DIV %s\n", num_t_to_string(&left), num_t_to_string(&right));
			return num_t_int_div(left, right);

		case T_REAL_DIV:
			left = N_visit(i, bin->left_child);
			right = N_visit(i, bin->right_child);
			printf("%s / %s\n", num_t_to_string(&left), num_t_to_string(&right));
			return num_t_float_div(left, right);

		default:
			printf("Non implemented operation for bin_op node: (type: %d, val: %s)\n", bin->t->type, bin->t->value);
			exit(1);
	}
}

num_T N_visit(interpreter_T* i, ast_node_T* node)
{
	//printf("Visit called on node with type %d\n", node->type);
	switch (node->type) 
	{
		case PROGRAM:
			visit_program(i, node);
			break;

		case BLOCK:
			visit_block(i, node);
			break;

		case VARDECL:
			visit_vardecl(i, node);
			break;

		case TYPE_SPEC:
			visit_type(i, node);
			break;

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

		ddefault:
			exit(420);
			break;
	}
	return (num_T) {.type = INTEGER, .value = (num_U) {.i = 0}};
}
