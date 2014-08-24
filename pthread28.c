#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

void *thread_function(void *arg);

int run_now=1;
pthread_mutex_t work_mutex;

int main()
{
    int res;
    int print_count1=0;
    pthread_t a_thread;
   
    if(pthread_mutex_init(&work_mutex,NULL)!=0)
    {
       perror("Mutex init failed");
	exit(1);
    }
    if(pthread_create(&a_thread,NULL,thread_function,NULL)!=0)
    {
         perror("Thread creation failed!");
         exit(1);
    }
   
    if(pthread_mutex_lock(&work_mutex)!=0)
    {
         perror("Lock failed");
   	 exit(1);
    }
    else
    {
        printf("main thread is sleeping\n");
       sleep(1);
    }
  
    if(pthread_mutex_unlock(&work_mutex)!=0)
    {
      	perror("unlock failed\n");
	exit(1);
    }
    else
    {
  	printf("main unlock\n");
    }
    pthread_mutex_destroy(&work_mutex);
    pthread_join(a_thread,NULL);
    exit(0);
}

void *thread_function(void *arg)
{
    int print_count2=0;

    sleep(1);
    if(pthread_mutex_lock(&work_mutex)!=0)
    {
        perror("Lock filed");
	exit(1);
    }
    else
        printf("function lock\n");
    while(print_count2++<5)
    {
	if(run_now==2)
  	{
	    printf("function thread is running\n");
  	    run_now=1;
	}

        else
        {
   	   printf("function thread is sleeping\n");
 	   sleep(2);
	}
     }
     if(pthread_mutex_unlock(&work_mutex)!=0)
      {
	   perror("unlock failed");
	   exit(1);
      }
	else
	   printf("function unlock\n");
      pthread_exit(NULL);
}


