#include<semaphore.h>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<pthread.h>
#include<stdlib.h>

void *thread_function(void *arg);
void print();   //share
sem_t *sem;
int val;

int main(int argc,char *argv[])
{
     int n=0;
     pthread_t a_thread;
     sem_t *bin_sem;

     if(argc!=2)
     {
     	printf("please input a file name!\n");
        exit(2);
     }

     sem=sem_open(argv[1],O_CREAT,0644,3);
     while(n++<5)
    {
	if((pthread_create(&a_thread,NULL,thread_function,NULL))!=0)
	{
		perror("Thread creation failed!\n");
		exit(1);
  	}
    }
    pthread_join(a_thread,NULL);
    sem_close(bin_sem);   //variable question  already sloution
    sem_unlink(argv[1]);
}

void *thread_function(void *arg)
{
     sem_wait(sem);
     print();
     sleep(1);
     sem_post(sem);
     printf("I'm finished,my tid is %d\n",(int)pthread_self());
}

void print()
{
    printf("I get it,my tid is %d\n",(int)pthread_self());
    sem_getvalue(sem,&val);
    printf("Now the value have %d\n",val);
}


