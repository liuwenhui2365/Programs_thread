#include<semaphore.h>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<pthread.h>
#include<stdlib.h>

void *thread_function(void *arg);
void print(void);
sem_t bin_sem;
int value;

int main()
{
    int n=0;
    pthread_t a_thread;
    if((sem_init(&bin_sem,0,2))!=0)
    {
       perror("sem_init");
   	exit(1);
    }
    while(n++<5)
    {
        if((pthread_create(&a_thread,NULL,thread_function,NULL))!=0)
       {
	    perror("Thread creation failed");
            exit(1);
       }
    }
    pthread_join(a_thread,NULL);
}

void *thread_function(void *arg)
{
    sem_wait(&bin_sem);
    print();
    sleep(1);
    sem_post(&bin_sem);
    printf("I finished,my pid is %d\n",pthread_self());
    pthread_exit(arg);
}

void print()
{
    printf("I get it,my tid is %d\n",pthread_self());
    sem_getvalue(&bin_sem,&value);
    printf("Now the value have %d\n",value);
}


