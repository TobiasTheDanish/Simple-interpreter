#include "include/strings.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char* to_lower(char* str)
{
	char* s = calloc(2, sizeof(char));
	size_t size = 0;

	while (size < strlen(str)-1) {
		s[size] = tolower(str[size]);
		size++;
		s = realloc(s, (size + 1) * sizeof(char));
	}

	return s;
}
