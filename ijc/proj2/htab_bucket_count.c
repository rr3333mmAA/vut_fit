/*------------------------------------------- HTAB BUCKET COUNT -----
|  Task: IJC-DU2
|  
|  File: htab_bucket_count.c
|
|  Author: Abayev Amirkhan
|  Login: xabaye00
|  Faculty: Information Technology, Brno University of Technology
|
|  Description: Count hash table array elements
|  Compiled: gcc 11.2.1
|
|  Date: 18.4.2022
*-------------------------------------------------------------------*/

#include "htab.h"
#include "htab_private.h"
 
size_t htab_bucket_count(const htab_t *t) 
{
	return t->array_size;
}
