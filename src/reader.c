#include "include/reader.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


char* read_file(char* filePath)
{
	FILE* file = fopen(filePath, "r");
	size_t capacity = 100;
	char* contents = calloc(capacity, sizeof(char));
	size_t size = 0;

	if (file != NULL)
	{
		while (!feof(file)) 
		{
			contents[size] = fgetc(file);
			size += 1;

			if (size == capacity) 
			{
				capacity *= 1.5;

				contents = realloc(contents, capacity * sizeof(char));
			}
		}

		fclose(file);

		return contents;
	}
	else 
	{
		perror("File not found");
		return "";
	}
}
