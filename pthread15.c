#include<pthread.h>
#include<stdio.h>

pthread_key_t tsd_key;
pthread_once_t key_once=PTHREAD_ONCE_INIT;

void once_routine(void)
{
    int status;

    status=pthread_key_create(&tsd_key,NULL);
    if(status=0)
    {
        printf("Key create success!My id is %u\n",(unsigned int)pthread_self());
    }
}

void *child_thread(void *arg)
{
    printf("I'm child,My id is %u\n",(unsigned int)pthread_self());
    pthread_once(&key_once,once_routine);
}

int main(int argc,char *argv[])
{
    pthread_t child_thread_id;
    pthread_create(&child_thread_id,NULL,child_thread,NULL);
    printf("I'm father,my id is %u\n",(unsigned int)pthread_self());
    pthread_once(&key_once,once_routine);
}
