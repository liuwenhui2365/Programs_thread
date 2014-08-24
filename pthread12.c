#include<pthread.h>
#include<string.h>

void *thr_fn1(void *arg)
{
    printf("thread1 returning\n");
    return((void *)1);
}

void *thr_fn2(void *arg)
{
    printf("thread2 exiting\n");
    return((void *)2);
}

int main()
{
   pthread_t tid1,tid2;
   void *tret;

   pthread_create(&tid1,NULL,thr_fn1,NULL);
   pthread_create(&tid2,NULL,thr_fn2,NULL);
   pthread_join(tid2,&tret);
   printf("thread1 exit code %d\n",(int)tret);
   pthread_join(tid1,&tret);
   printf("thread2 exit code %d\n",(int)tret);
   exit(0);
}
