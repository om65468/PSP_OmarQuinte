#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>


void main() {
  pid_t pid2, pid3, pid4, pid5, pid6, prueb5, prueb6;

  prueb5=getpid();
  pid2=fork();
  
  if(pid2==0){
  prueb6=getpid();
  	pid3=fork();
  	if(pid3!=0){
  	printf("Mi pid2 es %d \n", getpid());
  		pid4=fork();
  		if(pid4==0){
  		printf("Mi pid4 es %d y el de mi abuelo es %d \n", getpid(), prueb5);
  			pid6=fork();
  			if(pid6!=0){
	  			wait(NULL);
	  		} else{
	  			printf("Mi pid6 es %d y el de mi abuelo es %d \n", getpid(), prueb6);
	  		}
  		}else{
  			wait(NULL);
  		}
  		wait(NULL);
  	}else{
  		pid5=fork();
  		if(pid5!=0){
  		printf("Mi pid5 es %d y el de mi abuelo es %d \n", getpid(), prueb5);
  			wait(NULL);
  		}else{
  			printf("Mi pid3 es %d y el de mi abuelo es %d \n", getpid(), prueb6);
  		}
  		
  	wait(NULL);
  	}
  	
  }else{
  	wait(NULL);
  }
  exit(0);
  }
