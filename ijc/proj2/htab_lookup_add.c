/*-------------------------------------------- HTAB LOOKUP ADD -----
|  Task: IJC-DU2
|  
|  File: htab_lookup_add.c
|
|  Author: Abayev Amirkhan
|  Login: xabaye00
|  Faculty: Information Technology, Brno University of Technology
|
|  Description: Find/Add new pair
|  Compiled: gcc 11.2.1
|
|  Date: 18.4.2022
*-------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "htab.h"
#include "htab_private.h"

char *allocate_string(const char *str) 
{
	char *dst = malloc(strlen(str) + 1);
	if (dst == NULL) return NULL;        
	strcpy(dst, str);                    
	return dst;    
}

struct htab_item *create_item(htab_key_t k) 
{
	char *key = allocate_string(k);
	htab_pair_t *pair = malloc(sizeof(htab_pair_t));
	struct htab_item *item = malloc(sizeof(struct htab_item));
	if (pair == NULL || key == NULL || item == NULL) 
	{
		free(key);
		free(pair);
		free(item);
		return NULL;
	}
	
	pair->key = key;
	pair->value = 1;
	item->pair = pair;
	item->next = NULL;
	
	return item;
}

htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key) 
{
	if (t == NULL || key == NULL) 
	{
		fprintf(stderr, "The htab or key is NULL");
		return NULL;
	}
	
	size_t index = htab_hash_function(key) % t->array_size;
	
	if (t->array[index] == NULL) 
	{
		t->array[index] = create_item(key);
		if (t->array[index] == NULL) 
		{
			fprintf(stderr, "Out Of Memory");
			return NULL;
		}
		
		t->items_size += 1;
		return t->array[index]->pair;
	}
	
	struct htab_item *item_ptr = t->array[index];
	
	while (item_ptr != NULL) 
	{
		if (strcmp(key, item_ptr->pair->key) == 0) 
		{
			item_ptr->pair->value++;
			return item_ptr->pair;
		}
		
		item_ptr = item_ptr->next;
	}
	
	item_ptr = create_item(key);
	
	if (item_ptr == NULL) 
	{
		fprintf(stderr, "Out Of Memory");
		return NULL;
	}
	
	t->items_size += 1;
	return item_ptr->pair;
}
