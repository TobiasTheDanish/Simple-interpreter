#ifndef TYPES_H
#define TYPES_H

typedef enum NUM_TAG_E
{
	FLOAT,
	INTEGER,
} num_E;

typedef union NUM_UNION
{
	float f;
	int i;
} num_U;

typedef struct NUM_STRUCT
{
	num_E type;
	num_U value;
} num_T;

num_T num_t_add(num_T a, num_T b);
num_T num_t_subtract(num_T a, num_T b);
num_T num_t_multiply(num_T a, num_T b);
num_T num_t_int_div(num_T a, num_T b);
num_T num_t_float_div(num_T a, num_T b);

char* num_t_to_string(num_T* n);
#endif // !TYPES_H
