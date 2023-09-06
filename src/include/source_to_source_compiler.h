#ifndef SOURCE_TO_SOURCE_COMPILER
#define SOURCE_TO_SOURCE_COMPILER

#include "ast_node.h"
#include "sym_table.h"
typedef struct SRC_TO_SRC_COMPILER_STRUCT
{
	scoped_sym_table_T* scope;
	char* output;
	size_t output_size;
} src_2_src_compiler_T;

src_2_src_compiler_T* init_src_to_src_compiler();

void SRC_visit(src_2_src_compiler_T* compiler, ast_node_T* node);

#endif
