#include "include/interpreter.h"
#include "include/ast_node.h"
#include "include/node_visitor.h"
#include "include/parser.h"
#include <stdio.h>
#include <stdlib.h>

interpreter_T* I_init(char* s)
{
	interpreter_T* i = malloc(sizeof(interpreter_T));
	i->p = P_init(s);

	return i;
}

int I_run(interpreter_T* i)
{
	ast_node_T* root = P_parse(i->p);

	printf("Result: %d\n", visit(root));

	return 0;
}

