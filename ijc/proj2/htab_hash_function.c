/*------------------------------------------ HTAB HASH FUNCTION -----
|  Task: IJC-DU2
|  
|  File: htab_hash_function.c
|
|  Author: Abayev Amirkhan
|  Login: xabaye00
|  Faculty: Information Technology, Brno University of Technology
|
|  Description: Hash of the string 
|  Compiled: gcc 11.2.1
|
|  Date: 18.4.2022
*-------------------------------------------------------------------*/

#include <stdint.h>
#include "htab.h"

size_t htab_hash_function(htab_key_t str) 
{
	uint32_t h=0;
	const unsigned char *p;
	
	for (p = (const unsigned char*) str; *p != '\0'; p++)
		h = 65599 * h + *p;
	
	return h;
}
