/*----------------------------------------------- HTAB FOR EACH -----
|  Task: IJC-DU2
|  
|  File: htab_for_each.c
|
|  Author: Abayev Amirkhan
|  Login: xabaye00
|  Faculty: Information Technology, Brno University of Technology
|
|  Description: Making function for all of the elements
|  Compiled: gcc 11.2.1
|
|  Date: 18.4.2022
*-------------------------------------------------------------------*/

#include "htab.h"
#include "htab_private.h"

void htab_for_each(const htab_t *t, void (*f)(htab_pair_t *data)) 
{
	if (t == NULL) 
	{
		return;
	}
	
	for (size_t i = 0; i < t->array_size; i++) 
	{
		struct htab_item *ptr = t->array[i];
		
		if (ptr == NULL) 
		{
			continue;
		}
		
		while (ptr != NULL) 
		{
			(*f)(ptr->pair);
			ptr = ptr->next;
		}
	}
}
