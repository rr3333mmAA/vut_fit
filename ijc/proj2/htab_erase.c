/*-------------------------------------------------- HTAB ERASE -----
|  Task: IJC-DU2
|  
|  File: htab_erase.c
|
|  Author: Abayev Amirkhan
|  Login: xabaye00
|  Faculty: Information Technology, Brno University of Technology
|
|  Description: Boolean operation for deleting elements
|		in hash table
|  Compiled: gcc 11.2.1
|
|  Date: 18.4.2022
*-------------------------------------------------------------------*/

#include <string.h>
#include <stdlib.h>
#include "htab.h"
#include "htab_private.h"
 
bool htab_erase(htab_t *t, htab_key_t key) 
{
	if (t == NULL || key == NULL) return false;

	size_t index = htab_hash_function(key) % t->array_size;
	struct htab_item *ptr = t->array[index];
	
	while (ptr != NULL) 
	{
		if (strcmp(key, ptr->pair->key) == 0) 
		{
			struct htab_item *to_free = ptr;
			ptr.next = to_free->next;
			free(to_free->pair->key);
			free(to_free->pair);
			free(to_free);
			return true;
		}
		ptr = ptr->next;
	}

	return false;
}
