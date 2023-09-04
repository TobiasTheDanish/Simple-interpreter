#include "include/parser.h"
#include "include/ast_node.h"
#include "include/token.h"
#include "include/strings.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NUM_KEYWORDS 8

token_T keywords[NUM_KEYWORDS] = {
	{ T_PROGRAM, "PROGRAM"},
	{ T_VAR, "VAR"},
	{ T_PROCEDURE, "PROCEDURE"},
	{ T_BEGIN, "BEGIN"},
	{ T_END, "END"},
	{ T_INT_DIV, "DIV"},
	{ T_INTEGER, "INTEGER"},
	{ T_REAL, "REAL"},
};

char* char_to_string(char c)
{
	char* s = malloc(2 * sizeof(char));
	s[0] = c;
	s[1] = '\0';

	return s;
}

parser_T* P_init(char* src)
{
	parser_T* parser = calloc(1, sizeof(parser_T));
	parser->src = src;
	parser->pos = 0;
	parser->current_char = parser->src[parser->pos];
	parser->current_token = P_get_next_token(parser);

	return parser;
}

void advance(parser_T* parser)
{
	parser->pos += 1;
	parser->current_char = parser->src[parser->pos];
}

token_T* advance_with_token(parser_T* parser, token_T* token)
{
	advance(parser);

	return token;
}

void clear_whitespace(parser_T* parser)
{
	while (parser->current_char == ' ' || parser->current_char == 10 || parser->current_char == 9) {
		advance(parser);
	}
}

void clear_comment(parser_T* parser) 
{
	advance(parser);

	while (parser->current_char != '}') 
	{
		advance(parser);
	}

	advance(parser);
}

char P_peek(parser_T* parser)
{
	size_t peek_pos = parser->pos + 1;

	if (peek_pos > strlen(parser->src) - 1)
	{
		printf("Tried to peek beyond end of file");
		exit(1);
	}
	else 
	{
		return parser->src[peek_pos];
	}
}

token_T* P_get_next_token(parser_T* parser)
{
	while (parser->current_char != '\0') 
	{
		clear_whitespace(parser);

		if (parser->pos >= strlen(parser->src)-1)
		{
			//printf("parser->pos is greater than length of src\n");
			return token_init(T_EOF, "\0");
		}

		if (isdigit(parser->current_char))
			return P_collect_token(parser, V_NUMBER);

		if (isalpha(parser->current_char) || parser->current_char == '_')
			return P_collect_id(parser);

		switch (parser->current_char) {
			case '{':
				clear_comment(parser);
				continue;
			case ':':
				if (P_peek(parser) == '=') {
					advance(parser);
					return advance_with_token(parser, token_init(T_ASSIGN, ":="));
				}
				return advance_with_token(parser, token_init(T_COLON, char_to_string(parser->current_char)));
			case '"':
				return P_collect_token(parser, V_STRING);
			case ',':
				return advance_with_token(parser, token_init(T_COMMA, char_to_string(parser->current_char)));
			case '.':
				return advance_with_token(parser, token_init(T_DOT, char_to_string(parser->current_char)));
			case ';':
				return advance_with_token(parser, token_init(T_SEMI, char_to_string(parser->current_char)));
			case '(':
				return advance_with_token(parser, token_init(T_LPAREN, char_to_string(parser->current_char)));
			case ')':
				return advance_with_token(parser, token_init(T_RPAREN, char_to_string(parser->current_char)));
			case '+':
				return advance_with_token(parser, token_init(T_PLUS, char_to_string(parser->current_char)));
			case '-':
				return advance_with_token(parser, token_init(T_MINUS, char_to_string(parser->current_char)));
			case '*':
				return advance_with_token(parser, token_init(T_MULTIPLY, char_to_string(parser->current_char)));
			case '/':
				return advance_with_token(parser, token_init(T_REAL_DIV, char_to_string(parser->current_char)));
		} 
	}

	return token_init(T_EOF, "\0");
}

token_T* get_id_token(char* id)
{
	for (size_t i = 0; i < NUM_KEYWORDS; i++) 
	{
		if (strcmp(to_lower(keywords[i].value), to_lower(id)) == 0)
				return &keywords[i];
	}

	return token_init(T_ID, id);
}

token_T* P_collect_id(parser_T* parser)
{
	char* id = calloc(2, sizeof(char));
	size_t i = 0;

	while (isalnum(parser->current_char) || parser->current_char == '_') {
		id[i] = parser->current_char;
		i = i + 1;
		id = realloc(id, (i+1)* sizeof(char));

		advance(parser);
	}

	return get_id_token(id);
}

token_T* collect_string(parser_T* parser)
{
	char* val = calloc(1, sizeof(char));
	size_t length = 0;

	while (parser->current_char != '"') {
		//printf("%c\n", parser->current_char);
		val[length] = parser->current_char;
		length += 1;
		val = realloc(val, (length + 1) * sizeof(char));

		advance(parser);
	}

	return token_init(T_STRING, val);
}

token_T* collect_number(parser_T* parser)
{
	char* val = calloc(1, sizeof(char));
	size_t length = 0;

	while (isdigit(parser->current_char)) {
		//printf("%c\n", parser->current_char);
		val[length] = parser->current_char;
		length += 1;
		val = realloc(val, (length + 1) * sizeof(char));

		advance(parser);
	}

	if (parser->current_char == '.') 
	{
		val[length] = parser->current_char;
		length += 1;
		val = realloc(val, (length + 1) * sizeof(char));

		advance(parser);

		while (isdigit(parser->current_char)) 
		{
			//printf("%c\n", parser->current_char);
			val[length] = parser->current_char;
			length += 1;
			val = realloc(val, (length + 1) * sizeof(char));

			advance(parser);
		}

		return token_init(T_REAL_CONST, val);
	}

	return token_init(T_INT_CONST, val);
}

token_T* P_collect_token(parser_T* parser, int type)
{
	switch (type) 
	{
		case V_NUMBER:
			return collect_number(parser);

		case V_STRING:
			return collect_string(parser);

		default:
			printf("Unexpected value type encountered with type %d\n", type);
			exit(1);
	}
}

void P_eat(parser_T* parser, int token_type)
{
	if (parser->current_token->type == token_type) 
	{
		//printf("%s\n", token_as_string(parser->current_token));
		parser->current_token = P_get_next_token(parser);
	}
	else 
	{
		printf("Unexpected token type, when trying to eat. Expected type: %d found: %d\n", token_type, parser->current_token->type);
		exit(1);
	}
}

unsigned char token_is_operation(token_T* token)
{
	unsigned char is_plus = token->type == T_PLUS;
	unsigned char is_minus = token->type == T_MINUS;
	unsigned char is_multiply = token->type == T_MULTIPLY;
	unsigned char is_divide = token->type == T_REAL_DIV || token->type == T_INT_DIV;

	return is_plus || is_minus || is_multiply || is_divide;
}

unsigned char operation_is_additive(token_T* token)
{
	unsigned char is_plus = token->type == T_PLUS;
	unsigned char is_minus = token->type == T_MINUS;

	return is_plus || is_minus;
}

unsigned char operation_is_multiplicative(token_T* token)
{
	unsigned char is_multiply = token->type == T_MULTIPLY;
	unsigned char is_divide = token->type == T_REAL_DIV || token->type == T_INT_DIV;

	return is_multiply || is_divide;
}

token_T* get_operation(parser_T* parser)
{
	token_T* operation = parser->current_token;

	P_eat(parser, operation->type);

	return operation;
}

ast_node_T* P_factor(parser_T* parser)
{
	token_T* token = parser->current_token;

	switch (token->type)
	{
		case T_PLUS:
			P_eat(parser, T_PLUS);
			return init_unary_op(token, P_factor(parser));

		case T_MINUS:
			P_eat(parser, T_MINUS);
			return init_unary_op(token, P_factor(parser));
			
		case T_LPAREN:
			P_eat(parser, T_LPAREN);
			ast_node_T* node = P_expr(parser);
			P_eat(parser, T_RPAREN);
			return node;

		case T_INT_CONST:
			P_eat(parser, T_INT_CONST);
			return init_num(token);

		case T_REAL_CONST:
			P_eat(parser, T_REAL_CONST);
			return init_num(token);
			
		case T_ID:
			return (ast_node_T*) P_variable(parser);

		default:
			printf("Unexpected token type, in P_factor. Type: %d current_char: %c\n", token->type, parser->current_char);
			return 0;
	}
}

ast_node_T* P_term(parser_T *parser)
{
	ast_node_T* left = P_factor(parser);

	while (token_is_operation(parser->current_token) && operation_is_multiplicative(parser->current_token)) 
	{
		token_T* op = get_operation(parser);

		left = init_bin_op(op, left, P_factor(parser));
	}

	return left;
}

ast_node_T* P_expr(parser_T* parser)
{
	ast_node_T* left = P_term(parser);

	while (token_is_operation(parser->current_token) && operation_is_additive(parser->current_token)) 
	{
		token_T* op = get_operation(parser);

		left = init_bin_op(op, left, P_term(parser));
	}

	return left;
}

ast_node_T* P_parse(parser_T* parser)
{
	ast_node_T* program = P_program(parser);

	if (parser->current_token->type != T_EOF) 
	{
		printf("Program did not reach end of file!\n");
	}

	return program;
}

ast_node_T* P_program(parser_T* parser)
{
	P_eat(parser, T_PROGRAM);
	var_node_T* var = P_variable(parser);
	char* name = var->name;

	P_eat(parser, T_SEMI);

	ast_node_T* block = P_block(parser);

	ast_node_T* node = init_program(name, block);

	P_eat(parser, T_DOT);

	return node;
}

ast_node_T* P_block(parser_T* parser)
{
	return P_declarations(parser);
}

ast_node_T* P_declarations(parser_T* parser)
{
	decl_node_T** declarations = malloc(sizeof(decl_node_T*));
	size_t count = 0;

	while (parser->current_token->type == T_VAR) 
	{
		P_eat(parser, T_VAR);

		while (parser->current_token->type == T_ID) 
		{
			decl_node_T* vardecl = (decl_node_T*) P_var_declaration(parser);
			declarations[count] = vardecl;
			count += 1;
			declarations = realloc(declarations, (count + 1) * sizeof(decl_node_T*));

			P_eat(parser, T_SEMI);
		}
	}

	while (parser->current_token->type == T_PROCEDURE)
	{
		param_node_T** params = malloc(sizeof(param_node_T*));
		size_t param_count = 0;

		P_eat(parser, T_PROCEDURE);

		char* proc_name = parser->current_token->value;

		P_eat(parser, T_ID);

		P_formal_params(parser, &params, &param_count);

		P_eat(parser, T_SEMI);

		ast_node_T* proc_block = P_block(parser);
		P_eat(parser, T_SEMI);

		declarations[count] = 
			(decl_node_T*) init_decl(PROCDECL, init_proc_decl(proc_name, params, param_count, proc_block));
		count += 1;
		declarations = realloc(declarations, (count + 1) * sizeof(decl_node_T*));
	}

	return init_block(declarations, count, P_compound_statement(parser));
}

void P_formal_params(parser_T* parser, param_node_T*** params, size_t* param_count) 
{
	param_node_T** p = malloc(sizeof(param_node_T*));
	size_t count = 0;

	if (parser->current_token->type != T_LPAREN) 
	{
		params = (void*) 0;
	}
	else
	{
		P_eat(parser, T_LPAREN);

		while (parser->current_token->type == T_ID) 
		{
			decl_node_T* decl = (decl_node_T*)P_var_declaration(parser);

			p[count] = init_param(decl->node->var);
			count += 1;
			p = realloc(p, (count + 1) * sizeof(param_node_T*));

			if (parser->current_token->type == T_SEMI) 
			{
				P_eat(parser, T_SEMI);
			}
		}

		P_eat(parser, T_RPAREN);
	}

	*params = p;
	*param_count = count;
}

ast_node_T* P_var_declaration(parser_T* parser)
{
	var_node_T** var_nodes = malloc(sizeof(var_node_T*));
	size_t count = 0;

	var_nodes[count] = init_var(parser->current_token);
	count += 1;

	P_eat(parser, T_ID);

	while (parser->current_token->type == T_COMMA) {
		P_eat(parser, T_COMMA);

		var_nodes = realloc(var_nodes, (count + 1) * sizeof(var_node_T*));
		var_nodes[count] = init_var(parser->current_token);
		count += 1;

		P_eat(parser, T_ID);
	}

	P_eat(parser, T_COLON);
	ast_node_T* type = P_type_spec(parser);

	return init_decl(VARDECL, init_var_decl(var_nodes, count, type));
}

ast_node_T* P_type_spec(parser_T* parser)
{
	token_T t = *parser->current_token;

	switch (t.type) 
	{
		case T_INTEGER:
			P_eat(parser, T_INTEGER);
			return init_type(&t);

		case T_REAL:
			P_eat(parser, T_REAL);
			return init_type(&t);

		default:
			printf("[P_type_spec]: Invalid token type, for type specification! Type: %d\n", t.type);
			exit(1);
	}
}

ast_node_T* P_compound_statement(parser_T* parser)
{
	P_eat(parser, T_BEGIN);
	compound_node_T* comp = P_statement_list(parser);
	P_eat(parser, T_END);

	return (ast_node_T*) comp;
}

compound_node_T* P_statement_list(parser_T* parser)
{
	compound_node_T* comp = (compound_node_T*) init_comp();

	ast_node_T* node = P_statement(parser);

	comp->children[comp->child_count] = node;
	comp->child_count++;
	comp->children = realloc(comp->children, (comp->child_count + 1) * sizeof(ast_node_T*));

	while (parser->current_token->type == T_SEMI) 
	{
		P_eat(parser, T_SEMI);

		node = P_statement(parser);

		comp->children[comp->child_count] = node;
		comp->child_count++;
		comp->children = realloc(comp->children, (comp->child_count + 1) * sizeof(ast_node_T*));
	}

	if (parser->current_token->type == T_ID) 
	{
		perror("Token type T_ID not allowed after parsing of statement");
	}

	return comp;
}

ast_node_T* P_statement(parser_T* parser)
{
	switch (parser->current_token->type) 
	{
		case T_BEGIN:
			return P_compound_statement(parser);

		case T_ID:
			return P_assign_statement(parser);

		default:
			return P_empty(parser);
	}
}

ast_node_T* P_assign_statement(parser_T* parser)
{
	var_node_T* left = P_variable(parser);
	token_T* t = parser->current_token;
	P_eat(parser, T_ASSIGN);
	ast_node_T* right = P_expr(parser);
	
	return init_assign(t, left, right);
}

var_node_T* P_variable(parser_T* parser)
{
	var_node_T* var = init_var(parser->current_token);

	P_eat(parser, T_ID);

	return var;
}

ast_node_T* P_empty(parser_T* parser)
{
	return init_noop();
}
