/*server.c*/
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<unistd.h>
#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc,char **argv)
{
    int shm_id;
    char *ptr;
    sem_t *sem;
    
    if(argc!=2)
    {
        printf("usage:shm_open<pathname>\n");
        exit(1);
    }
    shm_id=shm_open(argv[1],O_RDWR|O_CREAT,0644);
    ftruncate(shm_id,100);
    sem=sem_open(argv[1],O_CREAT,0644,1);
    ptr=mmap(NULL,100,PROT_READ|PROT_WRITE,MAP_SHARED,shm_id,0);
    strcpy(ptr,"\0");
    while(1)
    {
        if((strcmp(ptr,"\0"))==0)
        {
           continue;
        }
        else
        {
            if((strcmp(ptr,"q\n"))==0)
             {
                 break;
             }
             sem_wait(sem);
             printf("server:%s",ptr);
             strcpy(ptr,"\0");
             sem_post(sem);
        }
        sem_unlink(argv[1]);
        shm_unlink(argv[1]);
    }
}
