/*shm_write.c>*/
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc,char **argv)
{
    int shm_id;
    struct stat buf;
    char *ptr;
     
    if(argc!=2)
    {
        printf("usage:shm_open<pathname>\n");
        exit(1);
    }
    shm_id=shm_open(argv[1],O_RDWR|O_CREAT,0644);
    ftruncate(shm_id,100);
    fstat(shm_id,&buf);
    ptr=mmap(NULL,buf.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,shm_id,0);
    strcpy(ptr,"hello linux");
    printf("%s\n",ptr);
    shm_unlink(argv[1]);
}
