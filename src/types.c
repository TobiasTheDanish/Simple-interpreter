#include "include/types.h"
#include <stdio.h>
#include <stdlib.h>

char* num_t_to_string(num_T* n)
{
	char* res = calloc(1, sizeof(char));

	switch (n->type) 
	{
		case INTEGER:
			sprintf(res, "num_T(integer, %d)", n->value.i);
			break;

		case FLOAT:
			sprintf(res, "num_T(float, %f)", n->value.f);
			break;
	}
	return res;
}

num_T num_t_add(num_T a, num_T b)
{
	num_T res;
	switch (a.type) 
	{
		case INTEGER:
			if (b.type == INTEGER)
			{
				res.type = INTEGER;
				res.value.i = a.value.i + b.value.i;
			}
			else 
			{
				res.type = FLOAT;
				res.value.f = a.value.i + b.value.f;
			}
			break;

		case FLOAT:
			res.type = FLOAT;
			if (b.type == INTEGER)
			{
				res.value.f = a.value.f + b.value.i;
			}
			else 
			{
				res.type = FLOAT;
				res.value.f = a.value.f + b.value.f;
			}
			break;
	}
	return res;
}

num_T num_t_subtract(num_T a, num_T b)
{
	num_T res;
	switch (a.type) 
	{
		case INTEGER:
			if (b.type == INTEGER)
			{
				res.type = INTEGER;
				res.value.i = a.value.i - b.value.i;
			}
			else 
			{
				res.type = FLOAT;
				res.value.f = a.value.i - b.value.f;
			}
			break;

		case FLOAT:
			res.type = FLOAT;
			if (b.type == INTEGER)
			{
				res.value.f = a.value.f - b.value.i;
			}
			else 
			{
				res.type = FLOAT;
				res.value.f = a.value.f - b.value.f;
			}
			break;
	}
	return res;
}

num_T num_t_multiply(num_T a, num_T b)
{
	num_T res;
	switch (a.type) 
	{
		case INTEGER:
			if (b.type == INTEGER)
			{
				res.type = INTEGER;
				res.value.i = a.value.i * b.value.i;
			}
			else 
			{
				res.type = FLOAT;
				res.value.f = a.value.i * b.value.f;
			}
			break;

		case FLOAT:
			res.type = FLOAT;
			if (b.type == INTEGER)
				res.value.f = a.value.f * b.value.i;
			else 
				res.value.f = a.value.f * b.value.f;
			break;
	}
	return res;
}

num_T num_t_int_div(num_T a, num_T b)
{
	num_T res;
	res.type = INTEGER;
	switch (a.type) 
	{
		case INTEGER:
			if (b.type == INTEGER)
				res.value.i = a.value.i / b.value.i;
			else 
				res.value.i = a.value.i / b.value.f;
			break;

		case FLOAT:
			if (b.type == INTEGER)
				res.value.i = a.value.f / b.value.i;
			else 
				res.value.i = a.value.f / b.value.f;
			break;
	}
	return res;
}

num_T num_t_float_div(num_T a, num_T b)
{
	num_T res;
	res.type = FLOAT;
	switch (a.type) 
	{
		case INTEGER:
			if (b.type == INTEGER)
				res.value.f = (float) a.value.i / (float) b.value.i;
			else 
				res.value.f = a.value.i / b.value.f;
			break;

		case FLOAT:
			if (b.type == INTEGER)
				res.value.f = a.value.f / b.value.i;
			else 
				res.value.f = a.value.f / b.value.f;
			break;
	}
	return res;
}
