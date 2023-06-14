#ifndef TOKEN_H
#define TOKEN_H

typedef struct TOKEN_S
{
	enum token_type {
		STRING,
		INTEGER,
		PLUS,
		MINUS,
		MULTIPLY,
		DIVIDE,
		LPAREN,
		RPAREN,
		ILLEGAL,
		EOF,
	} type;

	char* value;
} token_t;

token_t* token_new(unsigned int type, char* value);
#endif
