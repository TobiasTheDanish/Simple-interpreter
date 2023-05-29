#ifndef TOKEN_H
#define TOKEN_H

typedef struct TOKEN_STRUCT
{
	enum  
	{
		T_STRING,
		T_INTEGER,
		T_PLUS,
		T_MINUS,
		T_EOF
	} type;

	char* value;
} token_T;

token_T* token_init(int type, char* value);

char* token_as_string(token_T* token);
#endif // !TOKEN_H
