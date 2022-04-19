/*--------------------------------------------------- HTAB FINE -----
|  Task: IJC-DU2
|  
|  File: htab_find.c
|
|  Author: Abayev Amirkhan
|  Login: xabaye00
|  Faculty: Information Technology, Brno University of Technology
|
|  Description: Find pair elements 
|  Compiled: gcc 11.2.1
|
|  Date: 18.4.2022
*-------------------------------------------------------------------*/

#include "htab.h"
#include "htab_private.h"
 
htab_pair_t *htab_find(htab_t *t, htab_key_t key) 
{
	if (t == NULL || key == NULL) 
	{
		return NULL;
	}
	
	size_t index = htab_hash_function(key) % t->array_size;
	struct htab_item *ptr = t->array[index];
	
	while (ptr != NULL) 
	{
		if (strcmp(key, ptr->pair->key) == 0) 
		{
			return ptr->pair;
		}
		
		ptr = ptr->next;
	}
	
	return NULL;
}
