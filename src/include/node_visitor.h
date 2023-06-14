#ifndef NODE_VISITOR_H
#define NODE_VISITOR_H

#include "ast_node.h"
#include "interpreter.h"

int visit(interpreter_T* i, ast_node_T* node);

#endif // !NODE_VISITOR_H
