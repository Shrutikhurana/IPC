#include<stdio.h>
#include<errno.h>
#include<unistd.h>
#include<sys/shm.h>
#include"s1.h"
#include<string.h>
#include<stdlib.h>

int main()
{


FILE *fp;

int shmid;
void *shared_memory=(void *)0;
struct shared *stuff;
char line[1000];

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



while(1)
{
 
 while(stuff->flag!=3)
 sleep(2); 
 
 if(strcmp(stuff->arr,"stop")==0)
 { 
  fp=fopen("stu.txt","r");
  printf("The contents of the file are\n");
  while(fgets(line,1000,fp))
  puts(line);
  //exit(0);
  break;
 } 

 fp=fopen("stu.txt","a");
 fputs(stuff->arr,fp);
 fputs("\n",fp);
 puts(stuff->arr);
 fclose(fp);

 stuff->flag=stuff->turn;
 
  
} 
  
  







return 0;
}
