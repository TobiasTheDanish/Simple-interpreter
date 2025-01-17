#include "include/interpreter.h"
#include "include/ast_node.h"
#include "include/list_map.h"
#include "include/node_visitor.h"
#include "include/parser.h"
#include "include/source_to_source_compiler.h"
#include "include/sym_table.h"
#include "include/symbol_table_visitor.h"
#include <stdio.h>
#include <stdlib.h>

interpreter_T* I_init(char* s)
{
	interpreter_T* i = malloc(sizeof(interpreter_T));
	i->p = P_init(s);
	i->sym_visitor = init_sym_table_visitor();
	i->global_scope = init_list_map(10);

	return i;
}

int I_run(interpreter_T* i)
{
	ast_node_T* root = P_parse(i->p);

	S_visit(i->sym_visitor, root);

	src_2_src_compiler_T* compiler = init_src_to_src_compiler();
	SRC_visit(compiler, root);
	printf("source to source compiler output:\n%s", compiler->output);

	N_visit(i, root);

	return 0;
}

