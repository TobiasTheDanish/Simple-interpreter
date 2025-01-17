#ifndef AST_NODE_H
#define AST_NODE_H

#include "types.h"
#include "token.h"
#include <stddef.h>
typedef struct AST_NODE_STRUCT
{
	enum 
	{
		PROGRAM,
		BLOCK,
		VARDECL,
		PROCDECL,
		PARAM,
		TYPE_SPEC,
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
	num_T val;

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

typedef struct type_node_T
{
	ast_node_T ast;
	token_T* token;
	char* val;
} type_node_T;

typedef struct VARDECL_NODE_STRUCT
{
	var_node_T** var;
	size_t count;
	type_node_T* type;
} vardecl_node_T;

typedef struct PARAM_NODE_STRUCT
{
	ast_node_T ast;
	vardecl_node_T* vardecl;
} param_node_T;

typedef struct PROCDECL_NODE_STRUCT
{
	char* name;
	param_node_T** params;
	size_t param_count;
	ast_node_T* block;
} procdecl_node_T;

typedef union DECLARATION_NODE_UNION
{
	vardecl_node_T* var;
	procdecl_node_T* proc;
} decl_node_U;

typedef struct DECLARATION_NODE_STRUCT
{
	ast_node_T ast;
	decl_node_U* node;
} decl_node_T;

typedef struct BLOCK_NODE_STRUCT
{
	ast_node_T ast;
	decl_node_T** decls;
	size_t decl_count;
	compound_node_T* comp;
} block_node_T;

typedef struct PROGRAM_NODE_STRUCT
{
	ast_node_T ast;
	char* name;
	block_node_T* block;

} program_node_T;

ast_node_T* init_program(char* name, ast_node_T* block);

ast_node_T* init_block(decl_node_T** decls, size_t count, ast_node_T* comp);

ast_node_T* init_comp();

procdecl_node_T* init_proc_decl(char* name, param_node_T** params, size_t param_count, ast_node_T* block);

vardecl_node_T* init_var_decl(var_node_T** var, size_t count, ast_node_T* type);

param_node_T* init_param(vardecl_node_T* vardecl);

ast_node_T* init_decl(unsigned int type, void* node);

ast_node_T* init_type(token_T* t);

ast_node_T* init_assign(token_T* t, var_node_T* l_child, ast_node_T* r_child);

var_node_T* init_var(token_T* t);

ast_node_T* init_num(token_T* t);

ast_node_T* init_bin_op(token_T* t, ast_node_T* l_child, ast_node_T* r_child);

ast_node_T* init_unary_op(token_T* t, ast_node_T* expr);

ast_node_T* init_noop();
#endif // !AST_NODE_H
