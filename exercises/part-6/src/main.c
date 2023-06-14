#include "include/interpreter.h"
#include "include/lexer.h"
#include <stdio.h>

int main()
{
	printf("calc> ");
	char* s;
	size_t len = 0;

	getline(&s, &len, stdin);

	interpreter_t* i = interpreter_new(lexer_new(s));
	printf("%d\n", interpreter_expr(i));

	return 0;
}
