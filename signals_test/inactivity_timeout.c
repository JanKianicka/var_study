#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>


int tprintf(const char *fmt, ...);
void sighandler(int signum);
void continuehandler(int signum);
void alarmhandler(int signum);
char buffer[200];

int main(void){

    sigset_t blockset, pending;
    int pendingcount;

    strcpy(buffer, "None\n");

    if(signal(SIGTERM, &sighandler) == SIG_ERR){
        tprintf("Could not register signal handler for SIGTERM.\n");
    }

    if(signal(SIGINT, &sighandler) == SIG_ERR){
        tprintf("Could not register signal handler for SIGINT.\n");
    }

    if(signal(SIGCONT, &continuehandler) == SIG_ERR){
            tprintf("Could not register signal handler for SIGCONT.\n");
        }

    if(signal(SIGALRM, &alarmhandler) == SIG_ERR){
            tprintf("Could not register signal handler for SIGALRM.\n");
        }

    sigemptyset(&blockset);
    sigaddset(&blockset, SIGTERM);
    sigaddset(&blockset, SIGINT);

    while(1){
        sigprocmask(SIG_BLOCK, &blockset, NULL);
        alarm(30);

        fgets(buffer, sizeof(buffer), stdin);
        tprintf("Input %s",buffer);

        /* Process pending signals */
        pendingcount = 0;
        if (sigismember(&pending, SIGINT)) pendingcount++;
        if (sigismember(&pending, SIGTERM)) pendingcount++;
        if (pendingcount) {
            tprintf("There are %d signals pending. \n", pendingcount);
        }
        /* Deliver them */
        sigprocmask(SIG_UNBLOCK, &blockset, NULL);

        if (strcmp(buffer, "exit\n") == 0){
            raise(SIGKILL);
        }
    }

    return(0);

}

int tprintf(const char *fmt, ...){
    va_list args;
    struct tm *tstruct;
    time_t tsec;

    tsec = time(NULL);
    tstruct = localtime(&tsec);

    printf("%02d:%02d:02d %5d| ",
            tstruct->tm_hour,
            tstruct->tm_min,
            tstruct->tm_sec,
            getpid());

    va_start(args, fmt);
    return vprintf(fmt, args);
}

void sighandler(int signum) {
    tprintf("Caught signal %d. \n", signum);
}

void continuehandler(int signum){
    tprintf("Continuing .. \n");
    tprintf("Your last input was: %s \n", buffer);
}

void alarmhandler(int signum){
    tprintf("No activity for 30 seconds, existing. \n");
    exit(0);
}
