#include<pthread.h>

void printids(const char *s)
{
     printf("%s pid:%u tid:%u \n",s,getpid(),pthread_self());
}

void *thr_fn(void *arg)
{
     printids("new thread:");
}

int main()
{
    int err;
    pthread_t tid;
    err=pthread_create(&tid,NULL,thr_fn,NULL);
    if(err=0)
     {
  	printf("can't create thread:%s \n",strerror(err));
     }
     printids("main thread:");
     sleep(2);
     exit(0);
}
