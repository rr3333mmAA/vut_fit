/*------------------------------------------------ HTAB PRIVATE -----
|  Task: IJC-DU2
|  
|  File: htab_private.h
|
|  Author: Abayev Amirkhan
|  Login: xabaye00
|  Faculty: Information Technology, Brno University of Technology
|
|  Description: Library with structures
|  Compiled: gcc 11.2.1
|
|  Date: 18.4.2022
*-------------------------------------------------------------------*/

#ifndef __HTAB_PRIVATE_H__
#define __HTAB_PRIVATE_H__

#include "htab.h"

struct htab_item 
{
	htab_pair_t *pair;
	struct htab_item *next;
};

struct htab 
{
	size_t items_size;
	size_t array_size;
	struct htab_item **array;
};


#endif
