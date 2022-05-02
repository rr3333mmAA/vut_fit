/*--------------------------------------------------- PROJECT 2 -----
|  Task: IOS - project 2
|  
|  File: proj2.c
|
|  Author: Abayev Amirkhan
|  Login: xabaye00
|  Faculty: Information Technology, Brno University of Technology
|
|  Description: Building H2O 
|  Compiled: gcc 11.2.1
|
|  Date: 2.5.2022
*-------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/prctl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <semaphore.h>
#include <time.h>
#include <stdarg.h>

// Global variables
int NO, NH, TI, TB, exp_noM;
FILE *stream;
struct shm_t
{
	sem_t mutex;
	sem_t bar_mutex;
	sem_t output;
	sem_t oxy_queue;
	sem_t hydro_queue;
	sem_t turnstile;
	sem_t turnstile2;
	int A, bar_c, oxygen, hydrogen, noM, used_o, used_h; 
} *shm;


// Printing error
void print_error(char *msg)
{
	fprintf(stderr, msg);
	exit(1);
}

// Printing outputs. (WriteFormatted reference)
void print_output(const char * format, ...)
{
	sem_wait(&shm->output);
	va_list args;
  	va_start (args, format);
	fprintf(stream, "%d: ", shm->A++);
  	vfprintf (stream, format, args);
	fflush(stream);
  	va_end (args);
	sem_post(&shm->output);
}

// Parsing arguments
void parse_args(int argc, char *argv[])
{
	if (argc != 5) print_error("Invalid number of arguments\n");

	NO = atoi(argv[1]);
	NH = atoi(argv[2]);
	TI = atoi(argv[3]);
	TB = atoi(argv[4]);

	if (NO <= 0) print_error("Invalid number of oxygen\n");
	if (NH <= 0) print_error("Invalid number of hydrogen\n");
	if (TI > 1000 || TI < 0) print_error("Invalid the maximum time of waiting before atoms going to queue\n");
	if (TB > 1000 || TB < 0) print_error("Invalid the maximum time of molecule forming\n");
}

// Initialization
void initialize()
{
	int shm_fd = shm_open("/xabaye00_proj2", O_CREAT | O_EXCL, 0666);
	shm = (struct shm_t *)mmap(NULL, sizeof(struct shm_t), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, shm_fd, 0);
	sem_init(&shm->mutex, 1, 1);
	sem_init(&shm->output, 1, 1);
	sem_init(&shm->oxy_queue, 1, 0);
	sem_init(&shm->hydro_queue, 1, 0);
	sem_init(&shm->turnstile, 1, 0);   // turnstile = Semaphore (0)
	sem_init(&shm->turnstile2, 1, 1);  // turnstile2 = Semaphore (1)
	sem_init(&shm->bar_mutex, 1, 1);   // bar_mutex = Semaphore (1)
	
}


void barrier()
{
	sem_wait(&shm->bar_mutex);
	shm->bar_c += 1;
	if (shm->bar_c == 3)
	{
		sem_wait(&shm->turnstile2);
		sem_post(&shm->turnstile);
	}
	sem_post(&shm->bar_mutex);

	sem_wait(&shm->turnstile);
	sem_post(&shm->turnstile);

	sem_wait(&shm->bar_mutex);
	shm->bar_c -= 1;
	if (shm->bar_c == 0)
	{
		sem_wait(&shm->turnstile);
		sem_post(&shm->turnstile2);
	}
	sem_post(&shm->bar_mutex);
	
	sem_wait(&shm->turnstile2);
	sem_post(&shm->turnstile2);
}

// Oxygen process
void oxygen(int idO)
{
	print_output("O %d: started\n", idO);
	usleep(1000 * (rand() % (TI + 1))); 
	print_output("O %d: going to queue\n", idO);

	sem_wait(&shm->mutex);
	shm->oxygen += 1;
	if (shm->hydrogen >= 2)
	{	
		sem_post(&shm->hydro_queue);
		sem_post(&shm->hydro_queue);
		shm->hydrogen -= 2;
		sem_post(&shm->oxy_queue);
		shm->oxygen -= 1;
	}
	else
	{
		sem_post(&shm->mutex);
	}
	
	sem_wait(&shm->oxy_queue);
	if (exp_noM == shm->used_o)
	{
		print_output("O %d: not enough H\n", idO);
		exit(0);
	}
	shm->used_o += 1;
	print_output("O %d: creating molecule %d\n", idO, shm->noM);
	usleep(1000 * (rand() % (TB + 1))); 

	
	barrier();	
	print_output("O %d: molecule %d created\n", idO, shm->noM);
	sem_post(&shm->mutex);

	if (exp_noM == shm->noM && shm->used_h != NH)
	{
		for (int j = 0; j <= (NH - shm->used_h); j++)
		{
			sem_post(&shm->mutex);
		}
	}
}

// Hydrogen process
void hydrogen(int idH)
{
	print_output("H %d: started\n", idH);
	usleep(1000 * (rand() % (TI + 1))); 
	print_output("H %d: going to queue\n", idH);

	sem_wait(&shm->mutex);
	shm->hydrogen += 1;
	if (exp_noM == shm->noM)
	{
		print_output("H %d: not enough O or H\n", idH);
		sem_post(&shm->oxy_queue);
		exit(0);
	}
	if (shm->hydrogen >= 2 && shm->oxygen >= 1)
	{	
		shm->noM += 1;
		sem_post(&shm->hydro_queue);
		sem_post(&shm->hydro_queue);
		shm->hydrogen -= 2;
		sem_post(&shm->oxy_queue);
		shm->oxygen -= 1;
	}
	else
	{
		sem_post(&shm->mutex);
	}

	sem_wait(&shm->hydro_queue);
	shm->used_h += 1;
	print_output("H %d: creating molecule %d\n", idH, shm->noM);
	usleep(1000 * (rand() % (TB + 1))); 

	barrier();
	print_output("H %d: molecule %d created\n", idH, shm->noM);

	if (exp_noM == shm->noM && shm->used_o != NO)
	{
		for (int j = 0; j <= (NO - shm->used_o); j++)
		{
			sem_post(&shm->oxy_queue);
		}
	}
}


void cleanup()
{
	fclose(stream);
	sem_destroy(&shm->mutex);
	sem_destroy(&shm->output);
	sem_destroy(&shm->oxy_queue);
	sem_destroy(&shm->hydro_queue);
	sem_destroy(&shm->turnstile);
	sem_destroy(&shm->turnstile2);
	sem_destroy(&shm->bar_mutex);
	munmap(shm, sizeof(struct shm_t));
	shm_unlink("/xabaye00_proj2");
}

// Main process
int main(int argc, char *argv[])
{
	// Seed
	srand(time(NULL) * getpid());

	// Parsing arguments
	parse_args(argc, argv);

	// Semaphore and mapping initialization
	initialize();

	// Open file
	if ((stream = fopen("proj2.out", "w")) == NULL) print_error("Can't open proj2.out file\n");
	
	// Variables
	shm->A = 1;
	shm->noM = 0;
	shm->used_o = 0;
	shm->used_h = 0;
	exp_noM = (NO >= NH / 2) ? NH / 2 : NO;

	for (int id = 1; id <= NO; id++)
	{
		pid_t pid = fork();
		if (pid == 0)
		{
			oxygen(id);
			exit(0);
		}
	}

	for (int id = 1; id <= NH; id++)
	{
		pid_t pid = fork();
		if (pid == 0)
		{
			hydrogen(id);
			exit(0);
		}
	}
	
	while(wait(NULL) > 0);

	cleanup();

	return 0;
}
