#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdarg.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>

char file2open[] = "File2open.txt";
FILE *f;

int tprintf(const char *fmt, ...);
void sighandler(int signum);


int main(void){
    char buffer[200];
    f = fopen(file2open, "w");

    if(signal(SIGTERM, &sighandler) == SIG_ERR){
        tprintf("Could not register signal handler.\n");
    }

    while(1){
        fgets(buffer, sizeof(buffer), stdin);
        tprintf("Input %s",buffer);
    }

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

void sighandler(int sifnum) {
    fclose(f);
    tprintf("File f closed.\n");
    tprintf("Caught signal SIGTERM. \n");
    exit(0);
}
