#ifndef AST_NODE_H
#define AST_NODE_H

#include "token.h"
typedef struct AST_NODE_STRUCT
{
	enum 
	{
		BIN_OP,
		NUM,
	} type;

} ast_node_T;

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

ast_node_T* init_bin_op(token_T* t, ast_node_T* l_child, ast_node_T* r_child);

ast_node_T* init_num(token_T* t);
#endif // !AST_NODE_H
