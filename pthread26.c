#include<semaphore.h>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>

void print(pid_t);
sem_t *sem;
int val;

int main(int argc,char *argv[])
{
    int n=0;
    sem=sem_open(argv[1],O_CREAT,0644,3);
    sem_getvalue(sem,&val);
    printf("The value have %d\n",val);
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
    }  
    wait();
    return 0;
}

void print(pid_t pid)
{
    printf("I get it,my pid is %d\n",pid);
    sem_getvalue(sem,&val);
    printf("Now the value have %d\n",val);
}
