/*server2.c*/
/*add "&" to file before process*/
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<unistd.h>
#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>

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
    sem=sem_open(argv[1],0);
    ptr=mmap(NULL,100,PROT_READ|PROT_WRITE,MAP_SHARED,shm_id,0);
    while(1)
    {
        sem_wait(sem);
        fgets(ptr,10,stdin);
        printf("user:%s",ptr);
        if((strcmp(ptr,"q\n"))==0)
        {
            exit(0);
        }
        sem_post(sem);
        sleep(1);
    }
    exit(0);
}
