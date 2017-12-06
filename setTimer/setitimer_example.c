/*
 * setitimer.c - simple use of the interval timer
 */

#include <stdio.h>
#include <sys/time.h>       /* for setitimer */
#include <unistd.h>     /* for pause */
#include <signal.h>     /* for signal */

#define INTERVAL 5000        /* number of milliseconds to go off */

/* function prototype */
void DoStuff(void);
FILE *f;
char msgName[] = "messageFile.xml";

int main(int argc, char *argv[]) {

  struct itimerval it_val;  /* for setting itimer */

  /* Upon SIGALRM, call DoStuff().
   * Set interval timer.  We want frequency in ms,
   * but the setitimer call needs seconds and useconds. */
  if (signal(SIGALRM, (void (*)(int)) DoStuff) == SIG_ERR) {
//  if (signal(SIGALRM, (int (*)(int)) DoStuff(5)) == SIG_ERR) {
    perror("Unable to catch SIGALRM");
    exit(1);
  }
  it_val.it_value.tv_sec =     INTERVAL/1000;
  it_val.it_value.tv_usec =    (INTERVAL*1000) % 1000000;
  it_val.it_interval = it_val.it_value;
  if (setitimer(ITIMER_REAL, &it_val, NULL) == -1) {
    perror("error calling setitimer()");
    exit(1);
  }

  while (1)
    pause();

}

/*
 * DoStuff
 */

void DoStuff(void) {
//int DoStuff(int a) {
	int retSystem = 0;
    f = fopen(msgName,"r");
    printf("Value of f %d \n",f);
    printf("Timer went off.\n");
    /* system() test */
    retSystem = system("ls -l");
    printf("retSystem %d\n",retSystem);
    retSystem = system("ls nonexist");
    printf("retSystem %d\n",retSystem);
    retSystem = system("other_small");
    printf("retSystem %d\n",retSystem);

    /* execl() test
     *  must be commented out because it terminates the current process.
     * */
//    retSystem = execl("/bin/ls", "ls", "-l", 0);
//    printf("retSystem %d\n",retSystem);

    /* fork() test. It must be terminated othevise it creates more and more child processes.
     * */
//    int return_value, pid;
//    printf("Forking process. \n");
//    pid = fork();
//    printf("The process id is %d "
//    	   "and return value is %d \n",
//    	   getpid(), return_value);
//    if (pid == 0){
//    	printf("Child process, pid %d\n",pid);
//    }
//    else{
//    	printf("Parent process, pid %d\n",pid);
//    }
//    exit(0);

    if(f!=0){
        printf("I am in message execution.\n");
        fclose(f);
        remove(msgName);

    }
}

