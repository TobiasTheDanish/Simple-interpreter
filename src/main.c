#include "include/interpreter.h"
#include "include/token.h"
#include <stdio.h>

int main()
{
	printf("calc> ");
	char* s;
	size_t len = 0;

	getline(&s, &len, stdin);

	interpreter_T* i = I_init(s);

	return I_run(i);
}
