#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>


void main() {
  pid_t pid2, pid3, pid4;
  int suma=0;
  
  pid2=fork();
  
  if(pid2==0){
  	pid3=fork();
  	if(pid3==0){
  		pid4=fork();
  		if(pid4!=0){
  			wait(NULL);
  		}
  	} else{
  		wait(NULL);
  	}
  } else{
  	wait(NULL);
  }
  suma=getpid()+getppid();
  printf("Mi pid es %d y el de mi padre es %d su suma es: %d \n", getpid(), getppid(), suma);
  
  
  }
