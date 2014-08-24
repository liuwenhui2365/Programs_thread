/*consumer and producer*/
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

#define MAX 5

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond=PTHREAD_COND_INITIALIZER;

typedef struct{
     char buffer[MAX];
     int how_many;
}BUFFER;

BUFFER share={"",0};
char ch='A';

void *read_some(void *);
void *write_some(void *);
pthread_mutex_t lock_it;//add

int main(void)
{
    pthread_t t_read;
    pthread_t t_write;

    pthread_create(&t_read,NULL,read_some,(void *)NULL);
    pthread_create(&t_write,NULL,write_some,(void *)NULL);
    pthread_join(t_write,(void**)NULL);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    exit(0);
}

void *read_some(void *junk)
{
   int n=0;
   pthread_t write_it;   //add
   printf("R %2d:staring\n",pthread_self());
   while(ch!='Z')
  {
     pthread_mutex_lock(&lock_it);
     if(share.how_many!=MAX)
     {
	share.buffer[share.how_many++]=ch++;
   	printf("R %2d:Got char[%c]\n",pthread_self(),ch-1);
        if(share.how_many==MAX)
	{
	    printf("R %2d:signaling full\n",pthread_self());
	    pthread_cond_signal(&write_it);
   	}
       pthread_mutex_unlock(&lock_it);
     }
    sleep(1);
    printf("R %2d:Exiting\n",pthread_self());
    return NULL;
   }
}

void *write_some(void *junk)
{
    int i;
    int n=0;
    pthread_t write_it;//add
    printf("w %2d:starting\n",pthread_self());

    while(ch!='Z')
    {
    	pthread_mutex_lock(&lock_it);
        printf("\nW %2d:Waiting\n",pthread_self());
      	while(share.how_many!=MAX)
        {
 	    pthread_cond_wait(&write_it,&lock_it);
	}
	printf("W %2d:writing buffer\n",pthread_self());
	for(i=0;share.buffer[i]&&share.how_many;++i,share.how_many--)
        {
	    putchar(share.buffer[i]);
	}
        pthread_mutex_unlock(&lock_it);
    }
    printf("W %2d:exiting\n",pthread_self());
    return NULL;
}

