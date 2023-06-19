#ifndef PARSER_H
#define PARSER_H
#include "ast_node.h"
#include "token.h"

#include <stddef.h>
enum values
{
	V_STRING,
	V_NUMBER,
};

typedef struct PARSER_STRUCT
{
	char current_char;
	char* src;
	size_t pos;
	token_T* current_token;
} parser_T;

parser_T* P_init(char* src);

char P_peek(parser_T* parser);

token_T* P_get_next_token(parser_T* parser);

token_T* P_collect_token(parser_T* parser, int type);

token_T* P_collect_id(parser_T* parser);

void P_eat(parser_T* parser, int token_type);

ast_node_T* P_factor(parser_T* parser);

ast_node_T* P_term(parser_T* parser);

ast_node_T* P_expr(parser_T* parser);

ast_node_T* P_parse(parser_T* parser);

ast_node_T* P_program(parser_T* parser);

ast_node_T* P_block(parser_T* parser);

ast_node_T* P_declarations(parser_T* parser);

ast_node_T* P_var_declaration(parser_T* parser);

ast_node_T* P_type_spec(parser_T* parser);

ast_node_T* P_compound_statement(parser_T* parser);

compound_node_T* P_statement_list(parser_T* parser);

ast_node_T* P_statement(parser_T* parser);

ast_node_T* P_assign_statement(parser_T* parser);

var_node_T* P_variable(parser_T* parser);

ast_node_T* P_empty(parser_T* parser);


#endif // !PARSER_H
