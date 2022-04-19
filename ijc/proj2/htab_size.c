/*--------------------------------------------------- HTAB SIZE -----
|  Task: IJC-DU2
|  
|  File: htab_size.c
|
|  Author: Abayev Amirkhan
|  Login: xabaye00
|  Faculty: Information Technology, Brno University of Technology
|
|  Description: Hash table size 
|  Compiled: gcc 11.2.1
|
|  Date: 18.4.2022
*-------------------------------------------------------------------*/

#include "htab.h"
#include "htab_private.h"
 
size_t htab_size(const htab_t *t) 
{
	return t->items_size;
}
