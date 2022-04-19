/*-------------------------------------------------------- WORDCOUNT -----
|  Task: IJC-DU2
|  
|  File: wordcount.c
|
|  Author: Abayev Amirkhan
|  Login: xabaye00
|  Faculty: Information Technology, Brno University of Technology
|
|  Description: Word counter 
|  Compiled: gcc 11.2.1
|
|  Date: 18.4.2022
*-------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "htab.h"

#define	HTAB_SIZE 4000
#define MAX_LENGTH 127

void print_data(htab_pair_t *data) 
{
	printf("%s\t%d\n", data->key, data->value);
}

int main() 
{
	htab_t *t = htab_init(HTAB_SIZE);
	char buf[MAX_LENGTH + 1];
    
	if (t == NULL) return 1;
    
	while (read_word(buf, MAX_LENGTH, stdin) != EOF) 
	{
		if (htab_lookup_add(t, buf) == NULL) 
		{
			htab_free(t);
			return 1;
		}
	}
    
	htab_for_each(t, print_data);
	
	return 0;
}
