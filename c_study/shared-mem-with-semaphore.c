/*
 * shared-mem-with-semaphore.c  - using a semaphore to synchronize access
 *                                to a shared memory segment.
 */

#include <stdio.h>	 /* standard I/O routines.               */
#include <sys/types.h>   /* various type definitions.            */
#include <sys/ipc.h>     /* general SysV IPC structures          */
#include <sys/shm.h>	 /* semaphore functions and structs.     */
#include <sys/sem.h>	 /* shared memory functions and structs. */
#include <unistd.h>	 /* fork(), etc.                         */
#include <wait.h>	 /* wait(), etc.                         */
#include <time.h>	 /* nanosleep(), etc.                    */
#include <stdlib.h>	 /* rand(), etc.                         */

#define SEM_ID    250	 /* ID for the semaphore.               */

/* define a structure to be used in the given shared memory segment. */
struct country {
    char name[30];
    char capital_city[30];
    char currency[30];
    int population;
};

/*
 * function: random_delay. delay the executing process for a random number
 *           of nano-seconds.
 * input:    none.
 * output:   none.
 */
void
random_delay()
{
    static int initialized = 0;
    int random_num;
    struct timespec delay;            /* used for wasting time. */

    if (!initialized) {
	srand(time(NULL));
	initialized = 1;
    }

    random_num = rand() % 10;
    delay.tv_sec = 0;
    delay.tv_nsec = 10*random_num;
    nanosleep(&delay, NULL);
}

/*
 * function: sem_lock. locks the semaphore, for exclusive access to a resource.
 * input:    semaphore set ID.
 * output:   none.
 */
void
sem_lock(int sem_set_id)
{
    /* structure for semaphore operations.   */
    struct sembuf sem_op;

    /* wait on the semaphore, unless it's value is non-negative. */
    sem_op.sem_num = 0;
    sem_op.sem_op = -1;
    sem_op.sem_flg = 0;
    semop(sem_set_id, &sem_op, 1);
}

/*
 * function: sem_unlock. un-locks the semaphore.
 * input:    semaphore set ID.
 * output:   none.
 */
void
sem_unlock(int sem_set_id)
{
    /* structure for semaphore operations.   */
    struct sembuf sem_op;

    /* signal the semaphore - increase its value by one. */
    sem_op.sem_num = 0;
    sem_op.sem_op = 1;   /* <-- Comment 3 */
    sem_op.sem_flg = 0;
    semop(sem_set_id, &sem_op, 1);
}

/*
 * function: add_country. adds a new country to the counties array in the
 *           shard memory segment. Handles locking using a semaphore.
 * input:    semaphore id, pointer to countries counter, pointer to
 *           counties array, data to fill into country.
 * output:   none.
 */
void
add_country(int sem_set_id, int* countries_num, struct country* countries,
	    char* country_name, char* capital_city, char* currency,
	    int population)
{
    sem_lock(sem_set_id);
    strcpy(countries[*countries_num].name, country_name);
    strcpy(countries[*countries_num].capital_city, capital_city);
    strcpy(countries[*countries_num].currency, currency);
    countries[*countries_num].population = population;
    (*countries_num)++;
    sem_unlock(sem_set_id);
}

/*
 * function: do_child. runs the child process's code, for populating
 *           the shared memory segment with data.
 * input:    semaphore id, pointer to countries counter, pointer to
 *           counties array.
 * output:   none.
 */
void
do_child(int sem_set_id, int* countries_num, struct country* counties)
{
    add_country(sem_set_id, countries_num, counties,
		"U.S.A", "Washington", "U.S. Dollar", 250000000);
    random_delay();
    add_country(sem_set_id, countries_num, counties,
		"Israel", "Jerusalem", "New Israeli Shekel", 6000000);
    random_delay();
    add_country(sem_set_id, countries_num, counties,
		"France", "Paris", "Frank", 60000000);
    random_delay();
    add_country(sem_set_id, countries_num, counties,
		"Great Britain", "London", "Pound", 55000000);
}

/*
 * function: do_parent. runs the parent process's code, for reading and
 *           printing the contents of the 'countries' array in the shared
 *           memory segment.
 * input:    semaphore id, pointer to countries counter, pointer to
 *           counties array.
 * output:   printout of countries array contents.
 */
void
do_parent(int sem_set_id, int* countries_num, struct country* countries)
{
    int i, num_loops;

    for (num_loops=0; num_loops < 5; num_loops++) {
        /* now, print out the countries data. */
        sem_lock(sem_set_id);
        printf("---------------------------------------------------\n");
        printf("Number Of Countries: %d\n", *countries_num);
        for (i=0; i < (*countries_num); i++) {
            printf("Country %d:\n", i+1);
            printf("  name: %s:\n", countries[i].name);
            printf("  capital city: %s:\n", countries[i].capital_city);
            printf("  currency: %s:\n", countries[i].currency);
            printf("  population: %d:\n", countries[i].population);
        }
        sem_unlock(sem_set_id);
	random_delay();
    }
}

int main(int argc, char* argv[])
{
    int sem_set_id;            /* ID of the semaphore set.           */
    union semun {              /* semaphore value, for semctl().     */
                int val;
                struct semid_ds *buf;
                ushort * array;
        } sem_val;    
    int shm_id;	      	       /* ID of the shared memory segment.   */
    char* shm_addr; 	       /* address of shared memory segment.  */
    int* countries_num;        /* number of countries in shared mem. */
    struct country* countries; /* countries array in shared mem.     */
    struct shmid_ds shm_desc;
    int rc;		       /* return value of system calls.      */
    pid_t pid;		       /* PID of child process.              */

    /* create a semaphore set with ID 250, with one semaphore   */
    /* in it, with access only to the owner.                    */
    sem_set_id = semget(SEM_ID, 1, IPC_CREAT | 0600);
    if (sem_set_id == -1) {
	perror("main: semget");
	exit(1);
    }

    /* intialize the first (and single) semaphore in our set to '1'. */
    sem_val.val = 1;
    rc = semctl(sem_set_id, 0, SETVAL, sem_val);
    if (rc == -1) {
	perror("main: semctl");
	exit(1);
    }

    /* allocate a shared memory segment with size of 2048 bytes. */
    shm_id = shmget(100, 2048, IPC_CREAT | IPC_EXCL | 0600);
    if (shm_id == -1) {
        perror("main: shmget: ");
        exit(1);
    }

    /* attach the shared memory segment to our process's address space. */
    shm_addr = shmat(shm_id, NULL, 0);
    if (!shm_addr) { /* operation failed. */
        perror("main: shmat: ");
        exit(1);
    }

    /* create a countries index on the shared memory segment. */
    countries_num = (int*) shm_addr;
    *countries_num = 0;
    countries = (struct country*) ((void*)shm_addr+sizeof(int));

    /* fork-off a child process that'll populate the memory segment. */
    pid = fork();
    switch (pid) {
	case -1:
	    perror("fork: ");
	    exit(1);
	    break;
	case 0:
	    do_child(sem_set_id, countries_num, countries);
	    exit(0);
	    break;
	default:
	    do_parent(sem_set_id, countries_num, countries);
	    break;
    }

    /* wait for child process's terination. */
    {
        int child_status;

        wait(&child_status);
    }

    /* detach the shared memory segment from our process's address space. */
    if (shmdt(shm_addr) == -1) {
        perror("main: shmdt: ");
    }

    /* de-allocate the shared memory segment. */
    if (shmctl(shm_id, IPC_RMID, &shm_desc) == -1) {
        perror("main: shmctl: ");
    }

    return 0;
}
