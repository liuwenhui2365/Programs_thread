#include<pthread.h>
#include<sched.h>

void *child_thread(void *arg)
{
    int policy;
    int max_priority,min_priority;
    struct sched_param param;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setinheritsched(&attr,PTHREAD_EXPLICIT_SCHED);
    pthread_attr_getinheritsched(&attr,&policy);
   
    if(policy==PTHREAD_EXPLICIT_SCHED)
    {
        printf("Inheritsched:PTHREAD_EXPLICIT_SCHED\n");
    }
    if(policy==PTHREAD_INHERIT_SCHED)
    {
        printf("Inheritsched:PTHREAD_INHERIT_SCHED\n");
    }

    pthread_attr_setschedpolicy(&attr,SCHED_RR);
    pthread_attr_getschedpolicy(&attr,&policy);
  
    if(policy==SCHED_FIFO)
        printf("Schedpolicy:SCHED_FIFO\n");
    if(policy==SCHED_RR)
       printf("Schedpolicy:SCHED_RR\n");
    if(policy==SCHED_OTHER)
       printf("Schedpolicy:SCHED_OTHER\n");
 
    sched_get_priority_max(max_priority);
    sched_get_priority_min(min_priority);

    printf("Max priority:%u\n",max_priority);
    printf("Min priority:%u\n",min_priority);

    param.sched_priority=max_priority;
    pthread_attr_setschedparam(&attr,&param);
    printf("sched_priority:%u\n",param.sched_priority);
    pthread_attr_destroy(&attr);
}

int main(int argc,char *argv[])
{
   pthread_t child_thread_id;
   
   pthread_create(&child_thread_id,NULL,child_thread,NULL);
   pthread_join(child_thread_id,NULL);
}
