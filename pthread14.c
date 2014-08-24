#include<pthread.h>

pthread_once_t once=PTHREAD_ONCE_INIT;
pthread_mutex_t mutex;

void once_init_routine(void)
{
    int status;
    status=pthread_mutex_init(&mutex,NULL);
    if(status==0)
        printf("Init success!,My id is %u\n",pthread_self());
}

void *child_thread(void *arg)
{
    printf("I'm child,My id is %u\n",pthread_self());
    pthread_once(&once,once_init_routine);
}

int main(int argc, char *argv[])
{
    pthread_t child_thread_id;
    pthread_create(&child_thread_id,NULL,child_thread,NULL);
    printf("I'm father,my id is %u\n",pthread_self());
    pthread_once(&once,once_init_routine);
    pthread_join(child_thread_id,NULL);
}
