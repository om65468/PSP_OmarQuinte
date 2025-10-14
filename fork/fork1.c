#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

// Siempre seguira el orden p2, p4, p3, p1 por que los procesos padres estan esperando a sus hijos

void main() {
  pid_t pid2, pid3, pid4;
  
  pid2=fork();
  
  if(pid2==0){
  	if(getpid()%2==0){
  		printf("Soy p2 mi pid es %d y el de mi padre es %d \n", getpid(), getppid());
  	} else{
  		printf("Soy p2 mi pid es %d \n", getpid());
  	}
  	
  }else{
  	pid3=fork();
  	if(pid3==0){
  	pid4=fork();
  	
  		if(pid4==0){
  			if(getpid()%2==0){
		  		printf("Soy p4 mi pid es %d y el de mi padre es %d \n", getpid(), getppid());
		  	}else{
		  		printf("Soy p4 mi pid es %d \n ", getpid());
		  	}
  		} else{
  			wait(NULL);
  			if(getpid()%2==0){
		  		printf("Soy p3 mi pid es %d y el de mi padre es %d \n", getpid(), getppid());
		  	}else{
		  		printf("Soy p3 mi pid es %d \n", getpid());
		  	}
  		}
  		
  	} else{
  	wait(NULL);
  	wait(NULL);
  		if(getpid()%2==0){
	  		printf("Soy p1 mi pid es %d y el de mi padre es %d \n", getpid(), getppid());
	  	} else{
	  		printf("Soy p1 mi pid es %d \n", getpid());
	  	}
  	}
  }
  exit(0);
  }
