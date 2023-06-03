#include "include/interpreter.h"
#include "include/token.h"
#include <stdio.h>

int main()
{
	printf("calc> ");
	char* s;
	size_t len = 0;

	getline(&s, &len, stdin);

	interpreter_T* interpreter = I_init(s);

	printf("Result: %d\n", I_expr(interpreter));

	return 0;
}
