#ifndef NODE_VISITOR_H
#define NODE_VISITOR_H

#include "interpreter.h"
#include "types.h"

num_T visit(interpreter_T* i, ast_node_T* node);

#endif // !NODE_VISITOR_H
