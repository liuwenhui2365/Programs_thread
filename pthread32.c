/*shm_open.c*/
#include<sys/mman.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>

int main(int argc,char **argv)
{
    int shm_id;

    if(argc!=2)
    {
        printf("usage:shm_open<pathname>\n");
        exit(1);
    }
    shm_id=shm_open(argv[1],O_RDWR|O_CREAT,0644);
    printf("shmid:%d\n",shm_id);
    shm_unlink(argv[1]);
}
