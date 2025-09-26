#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

void main() {
  pid_t pid2, pid3;
  
  pid2=fork();
  
  if(pid2==0){
  	pid3=fork();
  	if(pid3==0){
  		printf("Soy p3 mi pid es %d y el de mi padre es %d", getpid(), getppid());
  	}else{
  		wait(NULL);
  		printf("\n Soy p2 mi pid es %d y el de mi padre es %d", getpid(), getppid());
  	}
  }else{
  	wait(NULL);
  	printf("\n Soy p1 mi pid es %d y el de mi hijo es %d", getpid(), pid2);
  	
  }
  }
