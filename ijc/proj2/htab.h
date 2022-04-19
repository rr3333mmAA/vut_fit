/*-------------------------------------------------- HTAB (lib) -----
|  Task: IJC-DU2
|  
|  File: htab.h
|
|  Author: Abayev Amirkhan
|  Login: xabaye00
|  Faculty: Information Technology, Brno University of Technology
|
|  Description: Hash table library 
|  Compiled: gcc 11.2.1
|
|  Date: 18.4.2022
*-------------------------------------------------------------------*/

#ifndef __HTAB_H__
#define __HTAB_H__

#include <string.h>
#include <stdbool.h>

// Hash table
struct htab;

// Hash table structure type
typedef struct htab htab_t;

// Types
typedef const char *htab_key_t;
typedef int htab_value_t;

// Hash table pair
typedef struct htab_pair {
    htab_key_t    key;
    htab_value_t  value;
} htab_pair_t;

// Function
size_t htab_hash_function(htab_key_t str);

// Tools
htab_t *htab_init(size_t n);
size_t htab_size(const htab_t *t);
size_t htab_bucket_count(const htab_t *t);
void htab_resize(htab_t *t, size_t newn);
htab_pair_t *htab_find(htab_t *t, htab_key_t key);
htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key);
bool htab_erase(htab_t *t, htab_key_t key);

// Hast table for all of items
void htab_for_each(const htab_t *t, void (*f)(htab_pair_t *data));

void htab_clear(htab_t * t);
void htab_free(htab_t * t);

#endif
