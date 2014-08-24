#include<pthread.h>
#include<stdio.h>

void *child_thread(void *arg)
{
     printf("child thread run!\n");
}

int main(int argc,char *argv[])
{
     pthread_t tid;
     pthread_attr_t attr;
     void *arg,*fn;//add 

     pthread_attr_init(&attr);
     pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
     pthread_create(&tid,&attr,fn,argc);
     pthread_attr_destroy(&attr);
     sleep(1);
}

