/*---------------------------------------------------------- IO -----
|  Task: IJC-DU2
|  
|  File: io.c
|
|  Author: Abayev Amirkhan
|  Login: xabaye00
|  Faculty: Information Technology, Brno University of Technology
|
|  Description: Getting one word
|  Compiled: gcc 11.2.1
|
|  Date: 18.4.2022
*-------------------------------------------------------------------*/

#include <stdlib.h>
#include <ctype.h>
 
#include "io.h"
		
int read_word(char *s, int max, FILE *f)
{
	int c;
	int i = 0;
	int j = 0;

	if (max <= 0) return -1;

	while ((c = fgetc(f)) != EOF)
	{
		if (isspace(c))
		{
			if (i == 0) continue;
			else break;
		}

		if (i >= max - 1)
		{
			j++;
			continue;
		}

		s[i++] = c;
	}

	if (i == 0) return -1;
	if (i > 0) s[i] = '\0';

	return i + j;
}
