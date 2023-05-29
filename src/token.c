#include "include/token.h"
#include <stdio.h>
#include <stdlib.h>

token_T* token_init(int type, char* value)
{
	token_T* token = calloc(1, sizeof(token_T));
	token->type = type;
	token->value = value;

	return token;
}

char* token_as_string(token_T* token)
{
	char* str = calloc(25, sizeof(char));
	sprintf(str, "TOKEN(%d, %s)", token->type, token->value);

	return str;
}
