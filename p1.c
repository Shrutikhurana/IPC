#include<stdio.h>
#include<errno.h>
#include<unistd.h>
#include<sys/shm.h>
#include"s1.h"
#include<string.h>
#include<stdlib.h>

int main()
{

int shmid;
void *shared_memory=(void *)0;
struct shared *stuff;



shmid=shmget((key_t)1334,sizeof(struct shared),0666|IPC_CREAT);
printf("Shmid is %d\n",shmid);
if(shmid==-1)
{
 fprintf(stderr,"Shmget failed\n");
 exit(EXIT_FAILURE);
}

shared_memory=shmat(shmid,(void *)0,0);
if(shared_memory==(void *)-1)
{
 fprintf(stderr,"shmat failed\n");
 exit(EXIT_FAILURE);
}

printf("Memory attached at %d\n",(int)shared_memory);
stuff=(struct shared *)shared_memory;

stuff->flag=1;
printf("Enter line of text\n");

while(1)
{
 
 while(stuff->flag!=1)
 sleep(2); 
 
 stuff->turn=2;
 gets(stuff->arr);
 //puts(stuff->arr);
 stuff->flag=3;

 if(strcmp(stuff->arr,"stop")==0)
 { break; } 
} 
  


return 0;
}
