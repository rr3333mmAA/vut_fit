/*-------------------------------------------------- HTAB CLEAR -----
|  Task: IJC-DU2
|  
|  File: htab_clear.c
|
|  Author: Abayev Amirkhan
|  Login: xabaye00
|  Faculty: Information Technology, Brno University of Technology
|
|  Description: Clear elements in hash table 
|  Compiled: gcc 11.2.1
|
|  Date: 18.4.2022
*-------------------------------------------------------------------*/


#include <stdlib.h>
#include "htab.h"
#include "htab_private.h"
 
void htab_clear(htab_t *t) 
{
	if (t == NULL) return;
    	
	for (size_t i = 0; i < t->array_size; i++) 
	{
		while (t->array[i] != NULL)
		{
			struct htab_item *ptr = t->array[i];
			free((void *)ptr->pair->key);
			free(ptr->pair);
			free(ptr);
			t->array[i] = ptr->next;
		}
	}

	t->items_size = 0;
}
