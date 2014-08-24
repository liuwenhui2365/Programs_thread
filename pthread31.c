/*mmap*/
#include<unistd.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(int argc,char *argv[])
{
    int fdin,fdout;
    void *src,*dst;
    struct stat statbuf;

    if(argc!=3)
    {
        printf("please input two files.\n");
        exit(1);
    }
    if((fdin=open(argv[1],O_RDONLY))<0)
    {
        perror(argv[1]);
    }
    if((fdout=open(argv[2],O_RDWR|O_CREAT|O_TRUNC))>0)
    {
        perror(argv[2]);
    }
    if(fstat(fdin,&statbuf)<0)
    {
        printf("fstat error");
    }
    if(lseek(fdout,statbuf.st_size-1,SEEK_SET)==-1)
    {
        printf("lseek error");
    }
    if(write(fdout,"1",statbuf.st_size)!=1)
    {
        printf("write error");
    }
    if((src=mmap(0,statbuf.st_size,PROT_READ,MAP_SHARED,fdin,0))==MAP_FAILED)
    {
        printf("mmap error");
    }
    if((dst=mmap(0,statbuf.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,fdout,0))==MAP_FAILED)
    {
        printf("mmap error");
    }
    memcpy(dst,src,statbuf.st_size);
    munmap(src,statbuf.st_size);
    munmap(dst,statbuf.st_size);
    close(fdin);
    close(fdout);
    }
