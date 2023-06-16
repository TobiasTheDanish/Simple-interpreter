#ifndef LIST_MAP_H
#define LIST_MAP_H

#include <stdbool.h>
#include <stddef.h>
#include "types.h"

typedef enum OPTION_ENUM
{
	Value,
	Err,
} option_E;

typedef union OPTION_UNION
{
	num_T val;
	char* err;
} option_U;

typedef struct OPTION_STRUCT
{
	option_E type;
	option_U val;
} option_T;

struct key_value
{
	char* key;
	num_T val;
};

struct list_map;

struct list_map* init_list_map(size_t capacity);

bool list_map_insert(struct list_map* map, char* key, num_T val);

option_T list_map_get(struct list_map* map, char* key);

void list_map_print(struct list_map* map);

void list_map_free(struct list_map* map);

#endif // !LIST_MAP_H
