/* execve.c */
/* example from man page of execve program */
/*
       We can use the second program to exec the first as follows:

           $ cc myecho.c -o myecho
           $ cc execve.c -o execve
           $ ./execve ./myecho
           argv[0]: ./myecho
           argv[1]: hello
           argv[2]: world
*/
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

/* And now lets try to combine with fopencookie function and new stream.
 * The goal is to test whether the syslog stream will be closed by execve function */
/* Copy over initializations from fopencookie_ex1. */

#include <syslog.h>

static char const *priov[] = {
"EMERG:",   "ALERT:",  "CRIT:", "ERR:", "WARNING:", "NOTICE:", "INFO:", "DEBUG:"
};

static size_t writer(void *cookie, char const *data, size_t leng)
{
    (void)cookie;
    int     p = LOG_DEBUG, len;
    do len = strlen(priov[p]);
    while (memcmp(data, priov[p], len) && --p >= 0);

    if (p < 0) p = LOG_INFO;
    else data += len, leng -= len;
    while (*data == ' ') ++data, --leng;

    syslog(p, "%.*s", leng, data);
    return  leng;
}

static int noop(void) {return 0;}
static cookie_io_functions_t log_fns = {
    (void*) noop, (void*) writer,(void*) noop, (void*) noop
};

void tolog(FILE **pfp)
{
    setvbuf(*pfp = fopencookie(NULL, "w", log_fns), NULL, _IOLBF, 0);
}

int
main(int argc, char *argv[])
{
   char *newargv[] = { NULL, "hello", "world", NULL };
   char *newenviron[] = { NULL };
   int num_son=0;
   int	p[2];
   char	c;

   FILE *stdoutback;
   FILE *stderrback;
   FILE *stderrback2;

   FILE   *childlog = NULL;/* stdout for child */
   char *outfile = "child_log.out";

   assert(argc == 2);  /* argv[1] identifies
						  program to exec */
   newargv[0] = argv[1];

   printf("I am before syslog switch.\n");
   /* perform backup of stderr/stdout */
   stdoutback = stdout;
   stderrback = stderr;

   /* opening child log file here */
   childlog = fopen(outfile, "w");

   /* Testing of syslog fopencookie */
   tolog(&stderr);
   fprintf(stderr, "execve: Message for syslog before execve execution.\n");

   pipe(p);
   num_son=fork();
   if (num_son == 0) /* child process */
   {
	   fprintf(stdout, "Child process, standard stdout before execve.\n");
	   fprintf(stderr, "Child process, syslog/stderr before execve.\n");
	   sleep(40);
	   /* This makes parent to run first and damages current implementation */
	   /* Looks like there is needed yet wait method in parent. */
	   /* It was enough to weak up child by writing to pipe
	    * before reopening the child log file */
	   read(p[0],&c,1);
	   close(p[0]);
	   close(p[1]);

	   //dup2(0,p[0]);
	   //dup2(2,1);
	   dup2(fileno(childlog), 1);
	   dup2(fileno(childlog), 2);

	   fprintf(stdout, "Child process, standard stdout after dup2 but before execve.\n");
	   execve(argv[1], newargv, newenviron);
	   /* None of these message has not been printed, that means *pfp has been closed. */
	   /* Even after longer experimenting it was not possible to
	    * print in child anything after execve into any stream.
	    * All of them are closed. */
	   fprintf(stdout, "Child process, standard stdout after execve.\n");
	   fprintf(stdoutback, "Child process, stdoutback after execve.\n");
	   fprintf(stderr, "Child process, syslog/stderr after execve.\n");
	   fprintf(stderrback2, "Child process, stderrback2 after execve.\n");

	   /* Here even this reopen is not executed, looks like it was closed by execve */
	   freopen(outfile, "w", childlog);
	   fprintf(childlog, "Child log, child process after execve.\n");

   }
   else /* farther process */
   {
	   /* wake the child */
	   write(p[1],"",1);
	   close(p[1]);
	   close(p[0]);

	   fprintf(stdout, "I am in parent, standard stdout.\n");
	   fprintf(stderr, "Writing to syslog/stderr from parent after fork and execve.\n");

	   /* whereas dup2 in combination with execve() closed the childlog stream, we have to reopen it */
	   freopen(outfile, "a", childlog);
	   fprintf(childlog, "Child log, parent process after execve.\n");
   }
   /*tolog(&stderr);*/
   fprintf(stderr, "execve: Message for syslog after execve execution.\n");

   printf("I am after syslog switch.");
   fprintf(stderr, "Writing to new/syslod stderr after execve in main.\n");
   fprintf(stderrback, "Writing to original stderrback after execve.\n");

   /* closing the child log file */
   fclose( childlog );

   perror("execve");   /* execve() only returns on error */
   exit(EXIT_FAILURE);
}
