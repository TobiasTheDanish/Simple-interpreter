#include "include/interpreter.h"
#include "include/list_map.h"
#include "include/reader.h"
#include "include/token.h"
#include <stdio.h>

int main()
{
	char* pascal = read_file("pascal/part-10-example.pas");
	printf("pascal src:\n%s\n", pascal);

	/*
	printf("calc> ");
	char* s;
	size_t len = 0;

	getline(&s, &len, stdin);
	*/

	interpreter_T* i = I_init(pascal);

	I_run(i);

	list_map_print(i->global_scope);
	list_map_free(i->global_scope);

	return 0;
}
