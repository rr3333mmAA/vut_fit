/*-------------------------------------------------------- TAIL -----
|  Task: IJC-DU2
|  
|  File: tail.c
|
|  Author: Abayev Amirkhan
|  Login: xabaye00
|  Faculty: Information Technology, Brno University of Technology
|
|  Description: Printing strings from end of the stream 
|  Compiled: gcc 11.2.1
|
|  Date: 18.4.2022
*-------------------------------------------------------------------*/
 


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_error(char *message)
{
	char header[7] = "Error:";
	fprintf(stderr, "\n%s %s\n\n", header, message);
}

void print_tail(FILE *stream, int lines)
{
	// Variables
	int c;
	int string_counter = 0;
	
	// Printing strings from end of the stream
	if (stream)
	{
		int i = 0;
		while (string_counter != lines + 1)
		{
			if (fseek(stream, i--, SEEK_END) == 0)
			{
				if ((c = fgetc(stream)) == '\n')
				{	
					string_counter++;
				}
			}
			else
			{
				string_counter = lines + 1;
				fseek(stream, 0, SEEK_SET);
			}
		}
		if (string_counter == lines + 1)
		{
			while ((c = fgetc(stream)) != EOF)
			{
				putchar(c);
			}
		}
		fclose(stream);
	}
	else
	{
		print_error("Invalid file");	
	}
}

int main(int argc, char *argv[])
{
	FILE *file;

	switch (argc)
	{
		case 1:
			print_tail(stdin, 10);
			break;
		case 2:
			if (strcmp(argv[1], "-n") == 0)
			{
				print_error("You have not entered the length of the tail\n\nExample: tail -n 20 filename.txt");
			}
			else
			{
				file = fopen(argv[1], "r");
				print_tail(file, 10);			
			}
			break;
		case 3:
			if (strcmp(argv[1], "-n") == 0 && atoi(argv[2]) != 0)
			{				
				print_tail(stdin, atoi(argv[2]));
			}
		    	else if (*argv[2] != '0')
			{	
				print_error("Invalid parameters");
			}
			break;
		case 4:
			if (strcmp(argv[1], "-n") == 0 && atoi(argv[2]) != 0)
			{
				file = fopen(argv[3], "r");
				print_tail(file, atoi(argv[2]));
			}
		    	else if (*argv[2] != '0')
			{	
				print_error("Invalid parameters");
			}
			break;
		default:
			print_error("Invalid number of parameters");
	}

	return 0;
}
