#include "include/list_map.h"
#include "include/node_visitor.h"
#include "include/strings.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

struct list_map
{
	struct key_value** kv_pairs;
	size_t cap;
	size_t count;
};

struct list_map* init_list_map(size_t capacity)
{
	struct list_map* map = malloc(sizeof(struct list_map));
	map->cap = capacity;
	map->count = 0;
	map->kv_pairs = calloc(map->cap, sizeof(struct key_value*));

	for (size_t i = 0; i < map->cap; i++)
	{
		map->kv_pairs[i] = calloc(1, sizeof(struct key_value));
	}

	return map;
}

bool list_map_insert(struct list_map* map, char* key, num_T val)
{
	if (map->count >= map->cap - 1)
		return false;

	//printf("Adding key: %s with val: %d\n", key, val);
	map->kv_pairs[map->count]->key = malloc(strlen(key) * sizeof(char));

	strcpy(map->kv_pairs[map->count]->key, key);
	map->kv_pairs[map->count]->val = val;

	//printf("Added key: %s with val: %d\n", map->kv_pairs[map->count]->key, map->kv_pairs[map->count]->val);

	map->count += 1;

	return true;
}

option_T list_map_get(struct list_map* map, char* key)
{
	option_T opt;

	for (size_t i = 0; i < map->count; i++)
	{
		if (strcasecmp(map->kv_pairs[i]->key, key) == 0) {
			//printf("matched key: '%s' with pair-key: '%s'\n", key, map->kv_pairs[i]->key);
			opt.type = Value;
			opt.val.val = map->kv_pairs[i]->val;
			return opt;
		}
	}

	opt.type = Err;
	sprintf(opt.val.err, "Attempt at accessing key not in map. Key: %s\n", key);

	return opt;
}

void list_map_print(struct list_map* map)
{
	for (size_t i = 0; i < map->count; i++)
	{
		char* key = map->kv_pairs[i]->key;
		num_T val = map->kv_pairs[i]->val;

		switch (val.type) 
		{
			case FLOAT:
				printf("var #%zu: %s = %f\n", i, key, val.value.f);
				break;

			case INTEGER:
				printf("var #%zu: %s = %d\n", i, key, val.value.i);
				break;
		}
	}
}

void list_map_free(struct list_map* map)
{
	if (map == NULL) return;

	for (size_t i = 0; i < map->count; i++)
	{
		free(map->kv_pairs[i]->key);
		free(map->kv_pairs[i]);
	}

	free(map);
}

