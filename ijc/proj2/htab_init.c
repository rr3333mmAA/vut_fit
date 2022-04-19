/*--------------------------------------------------- HTAB INIT -----
|  Task: IJC-DU2
|  
|  File: htab_init.c
|
|  Author: Abayev Amirkhan
|  Login: xabaye00
|  Faculty: Information Technology, Brno University of Technology
|
|  Description: Create hash table 
|  Compiled: gcc 11.2.1
|
|  Date: 18.4.2022
*-------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#include "htab.h"
#include "htab_private.h"

htab_t *htab_init(size_t n) 
{
	if (n == 0) 
	{
		fprintf(stderr, "n have to be at least 1");
		return NULL;
	}
	
	htab_t *data = malloc(sizeof(htab_t));
	
	if (data == NULL) 
	{
		fprintf(stderr, "Out Of Memory");
		return NULL;
	}
	
	data->items_size = 0;
	data->array_size = n;
	data->array = malloc(sizeof(struct htab_item *) *n);
	
	if (data->array == NULL) 
	{
		fprintf(stderr, "Out Of Memory");
		free(data);
		return NULL;
	}
	
	for (size_t i = 0; i < n; i++) 
	{
		data->array[i] = NULL;
	}
	
	return data;
}
