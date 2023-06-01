#ifndef TOKEN_H
#define TOKEN_H

typedef struct TOKEN_STRUCT
{
	enum  
	{
		T_STRING,
		T_INTEGER,
		T_LPAREN,
		T_RPAREN,
		T_PLUS,
		T_MINUS,
		T_MULTIPLY, 
		T_DIVIDE,
		T_EOF
	} type;

	char* value;
} token_T;

token_T* token_init(int type, char* value);

char* token_as_string(token_T* token);
#endif // !TOKEN_H
