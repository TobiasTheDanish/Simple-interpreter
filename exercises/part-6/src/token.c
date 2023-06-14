#include "include/token.h"
#include <stdlib.h>


token_t* token_new(unsigned int type, char* value)
{
	token_t* token = malloc(sizeof(token_t));
	token->type = type;
	token->value = value;

	return token;
}
