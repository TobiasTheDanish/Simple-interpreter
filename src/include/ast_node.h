#ifndef AST_NODE_H
#define AST_NODE_H

#include "token.h"
#include <stddef.h>
typedef struct AST_NODE_STRUCT
{
	enum 
	{
		COMPOUND,
		ASSIGN,
		VAR,
		NUM,
		BIN_OP,
		UNARY_OP,
		NOOP,
	} type;

} ast_node_T;

union var_val
{
	char* c;
	int i;
};

typedef struct COMPOUND_NODE_STRUCT
{
	ast_node_T ast;
	ast_node_T** children;
	size_t child_count;
} compound_node_T;

typedef struct ASSIGN_NODE_STRUCT
{
	ast_node_T ast;
	token_T* t;
	struct VAR_NODE_STRUCT* left_child;
	struct AST_NODE_STRUCT* right_child;
} assign_node_T;

typedef struct VAR_NODE_STRUCT
{
	ast_node_T ast;
	token_T* t;
	char* name;
} var_node_T;

typedef struct NUM_NODE_STRUCT
{
	ast_node_T ast;
	token_T* t;
	int val;

} num_node_T;

typedef struct BIN_OP_NODE_STRUCT
{
	ast_node_T ast;
	token_T* t;
	struct AST_NODE_STRUCT* left_child;
	struct AST_NODE_STRUCT* right_child;

} bin_op_node_T;

typedef struct UNARY_OP_NODE_STRUCT
{
	ast_node_T ast;
	token_T* t;
	ast_node_T* expr;
} unary_op_node_T;

ast_node_T* init_comp();

ast_node_T* init_assign(token_T* t, var_node_T* l_child, ast_node_T* r_child);

var_node_T* init_var(token_T* t);

ast_node_T* init_num(token_T* t);

ast_node_T* init_bin_op(token_T* t, ast_node_T* l_child, ast_node_T* r_child);

ast_node_T* init_unary_op(token_T* t, ast_node_T* expr);

ast_node_T* init_noop();
#endif // !AST_NODE_H
