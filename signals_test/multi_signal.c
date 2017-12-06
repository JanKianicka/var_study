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
char buffer[200];

int main(void){

    strcpy(buffer, "None\n");

    if(signal(SIGTERM, &sighandler) == SIG_ERR){
        tprintf("Could not register signal handler for SIGTERM.\n");
    }

    if(signal(SIGINT, &sighandler) == SIG_ERR){
        tprintf("Could not register signal handler for SIGINT.\n");
    }

    while(1){
        fgets(buffer, sizeof(buffer), stdin);
        tprintf("Input %s",buffer);
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
