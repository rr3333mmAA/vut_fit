/*--------------------------------------------------- HTAB FREE -----
|  Task: IJC-DU2
|  
|  File: htab_free.c
|
|  Author: Abayev Amirkhan
|  Login: xabaye00
|  Faculty: Information Technology, Brno University of Technology
|
|  Description: Free allocated hash table
|  Compiled: gcc 11.2.1
|
|  Date: 18.4.2022
*-------------------------------------------------------------------*/

#include <stdlib.h>
#include "htab.h"
#include "htab_private.h"

void htab_free(htab_t *t)
{
	htab_clear(t);
	free(t);
}
