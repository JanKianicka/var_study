#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define reading 0
#define writing 1

main()
{
    int num_son,n;
    int *status;
    char c;

    /* don't need 4 file descriptors */
    int pipe_father_son[2],pipe_son_father[2];

    printf("Father: I am the father and my pid is %d \n", getpid());

    /* single pipe() call is enough as file descriptors will be shared by all */
    pipe(pipe_son_father);
    pipe(pipe_father_son);

    int i;
    for(i=0; i<3; i++)
    {
        num_son=fork();
        if(num_son==-1)
        {
            printf("creation error \n");
            exit(1);
        }
        if(num_son!=0)    //father process
        {
            char message[15];
            int n,num;

            //the father send the son his number
            num = num_son;

            /* Remove all close() calls as file descriptors are shared by all processes i.e. 1 parent + 3 children */
            close(pipe_father_son[reading]);
            n=write(pipe_father_son[writing],&num,sizeof(num));

            //the father receives a message from his son
            ////close the pipe on write to read in it
            close(pipe_son_father[writing]);
            n=read(pipe_son_father[reading],&message,sizeof(message));
            //printf("Father: i received %s\n",message);

            //the father replies to his son
            strcpy(message,"you are welcome");
            n=write(pipe_father_son[writing],&message,sizeof(message));

            //closes the pipes
            close(pipe_father_son[writing]);
            close(pipe_son_father[reading]);

            sleep(1);

        }
        else    //son process
        {
            int num_process,num_process_father,num;
            char message[15];

            num_process=getpid();
            num_process_father=getppid();

            //the son receives his number from his father
            close(pipe_father_son[writing]);
            n=read(pipe_father_son[reading],&num,sizeof(num));
            printf("Son: %d my pid is %d and i received %d from my father %d \n",i,num_process,num,getppid());

            //the son thanks his father
            printf("Son (%d) before close pipe_son_father.\n",getpid());
            close(pipe_son_father[reading]);
            strcpy(message,"thanks");

            n=write(pipe_son_father[writing],&message,sizeof(message));

            //the son receives the you are welcome message from his father
            n=read(pipe_father_son[reading],&message,sizeof(message));
            printf("Son (%d): I received %s\n",getpid(),message);

            //closes the pipes
            close(pipe_father_son[reading]);
            close(pipe_son_father[writing]);

            sleep(10);
            exit(num_son);

        }

    }

    for(i=0; i<3; i++)
    {
        wait(&status);
        printf("Father: my son %d is over\n",i,(int) status/256);
        sleep(1);
    }
}
