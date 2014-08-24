#include<pthread.h>
#include<stdio.h>

void cleanup(void *arg)
{
    printf("cleanup: %s\n",(char *)arg);
}

void *thr_fn(void *arg)
{
    printf("thread start\n");
    pthread_cleanup_push(cleanup,"thread first handler");
    pthread_cleanup_push(cleanup,"thread second handler");
    printf("thread push complete\n");
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
}

int main()
{
    pthread_t tid;
    void *tret;
    pthread_create(&tid,NULL,thr_fn,(void *)1);
    pthread_join(tid,&tret);
    printf("thread exit code %d\n",(int)tret);
}


