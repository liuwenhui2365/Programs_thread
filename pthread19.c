/*semunlink.c*/
#include<semaphore.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>

int main(int argc,char **argv)
{
     sem_t *sem;
     int val;
     if(argc!=2)
     { 
  	printf("please input a file name!\n");
   	exit(2);
     }
     if((sem_unlink(argv[1]))!=0)
 	perror("sem_unlink");
     else
 	printf("success");
     exit(0);
}
