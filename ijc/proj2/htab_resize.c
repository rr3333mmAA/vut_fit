/*------------------------------------------------ HTAB RESIZE -----
|  Task: IJC-DU2
|  
|  File: htab_resize.c
|
|  Author: Abayev Amirkhan
|  Login: xabaye00
|  Faculty: Information Technology, Brno University of Technology
|
|  Description: Resizing hash table
|  Compiled: gcc 11.2.1
|
|  Date: 18.4.2022
*-------------------------------------------------------------------*/

#include <stdlib.h>
#include "htab.h"
#include "htab_private.h"

void htab_destroy(htab_t *t) 
{
	for (size_t i = 0; i < t->array_size; i++) 
	{
		if (t->array[i] == NULL) 
		{
			continue;
		}
		
		struct htab_item *ptr = t->array[i];
		while (ptr != NULL) 
		{
			struct htab_item *next = ptr->next;
			free(ptr);
			ptr = next;
		}
	}
	
	free(t->array);
	free(t);
}

void htab_resize(htab_t *t, size_t newn) 
{
	if (t == NULL || newn == 0) 
	{
		return;
	}
	
	htab_t *new_htab = htab_init(newn);
	if (new_htab == NULL) return;
	
	for (size_t i = 0; i < t->array_size; i++) 
	{
		struct htab_item *ptr = t->array[i];
		
		while (ptr != NULL) 
		{
			size_t nindex = htab_hash_function(ptr->pair->key) % newn;
			struct htab_item *item = malloc(sizeof(struct htab_item));
			
			if (item == NULL) 
			{
				htab_destroy(new_htab);
				return;
			}
			
			item->pair = ptr->pair;
			item->next = NULL;
			
			if (new_htab->array[nindex] == NULL) 
			{
				new_htab->array[nindex] = item;
			} 
			else
			{
				struct htab_item *n = new_htab->array[nindex];
				
				while (n->next != NULL) 
				{
					n = n->next;
				}
				
				n->next = item;
			}
			
			ptr = ptr->next;
		}
	}
	
	new_htab->items_size = t->items_size;
	htab_t *tmp = t;
	t = new_htab;
	htab_destroy(tmp);
}
