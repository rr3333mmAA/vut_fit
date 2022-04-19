#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Global variables
int A = 0;
int idO = 1;
int idH = 1;

int rand_interval(int l, int u)
{
	return (rand() % (u - l + 1)) + l;
}

// Oxygen process
void oxygen(int TI)
{
	printf("%d: O %d: started\n", A++, idO++);
	usleep(rand_interval(0, TI));
	printf("AOAOAOAOAO\n");
}

// Main process
int main(int argc, char *argv[])
{
	(void)argc;

	// int NO = atoi(argv[1]);
	// int NH = atoi(argv[2]);
	int TI = atoi(argv[3]);
	// int TB = atoi(argv[4]);
	
	oxygen(TI);

	return 0;
}
