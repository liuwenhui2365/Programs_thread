/*shm_show.c*/
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc,char **argv)
{
    int shm_id;
    struct stat buf;
    if(argc!=2)
    {
        printf("usage:shm-open<pathname>\n");
        exit(1);
    }
    shm_id=shm_open(argv[2],O_RDWR|O_CREAT,0644);
    ftruncate(shm_id,100);
    fstat(shm_id,&buf);
    printf("uid_t:%d\n",buf.st_uid);
    printf("git_t:%d\n",buf.st_gid);
    printf("size:%d\n",(int)buf.st_size);
}

