#include<semaphore.h>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>

void print(pid_t);
sem_t *sem;
int val;

int main(int argc,char *argv[])
{
    int n=0;
    if(argc!=2)
    {
       printf("please input a file name!\n");
       exit(1);
    }
    sem=sem_open(argv[1],O_CREAT,0644,2);
    while(n++<5)
    {
       if(fork()==0)
       	{
		sem_wait(sem);
		print(getpid());
		sleep(1);
		sem_post(sem);
		printf("I'm finished,my pid is %d\n",getpid());
           	return 0;
        }
     wait();
     sem_close(sem);
     sem_unlink(argv[1]);
     exit(0);
    }
}

void print(pid_t pid)
{

   printf("I get it,my pid is %d\n",pid);
   sem_getvalue(sem,&val);
   printf("Now the value have %d\n",val);
}
