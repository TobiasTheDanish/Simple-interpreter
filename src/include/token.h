#ifndef TOKEN_H
#define TOKEN_H

typedef struct TOKEN_STRUCT
{
	enum  
	{
		T_PROGRAM,
		T_VAR,
		T_PROCEDURE,
		T_COLON,
		T_COMMA,
		T_BEGIN,
		T_END,
		T_DOT,
		T_ID,
		T_ASSIGN,
		T_SEMI,
		T_STRING,
		T_INTEGER,
		T_REAL,
		T_STRING_CONST,
		T_INT_CONST,
		T_REAL_CONST,
		T_LPAREN,
		T_RPAREN,
		T_PLUS,
		T_MINUS,
		T_MULTIPLY, 
		T_INT_DIV,
		T_REAL_DIV,
		T_EOF
	} type;

	char* value;
} token_T;

token_T* token_init(int type, char* value);

char* token_as_string(token_T* token);
#endif // !TOKEN_H
