/*---------------------------------------------------- IO (lib) -----
|  Task: IJC-DU2
|  
|  File: io.h
|
|  Author: Abayev Amirkhan
|  Login: xabaye00
|  Faculty: Information Technology, Brno University of Technology
|
|  Description: Library for getting one word
|  Compiled: gcc 11.2.1
|
|  Date: 18.4.2022
*-------------------------------------------------------------------*/

#ifndef __IO_H__
#define __IO_H__

#include <stdio.h>

// Reading 1 word
int read_word(char *s, int max, FILE *f);

#endif
