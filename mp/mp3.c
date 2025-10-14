#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

void main() {
  pid_t pid2, pid3;
  
  pid2=fork();
  if(pid2==0){
  	sleep(10);
  	printf("Despierto");
  }else{
  	pid3=fork();
  	if(pid3==0){
  		printf("Soy p3 mi pid es %d y el de mi padre es %d", getpid(), getppid());
  	}else{
  		wait(NULL);
  		wait(NULL);
  		printf("\n Padre: %d", getpid());
  	}
  }
  exit(0);
  }
