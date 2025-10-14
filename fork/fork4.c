#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>


void main() {
  pid_t pid2, pid3, pid4, pid5, pid6, acumulado;
  
  pid6=getpid();
  pid2=fork();
  if(pid2==0){
  	pid5=fork();
  	if(pid5==0){
  		if(getpid()%2==0){
  			acumulado=pid2+getpid()+pid6+10;
  			printf("Mi pid5 es %d y el acumulado es %d \n", getpid(), acumulado);
  		}else{
  			acumulado=pid2+getpid()+pid6-100;
  			printf("Mi pid5 es %d y el acumulado es %d \n", getpid(), acumulado);
  		}
  		
  	}else{
  	wait(NULL);
  		if(getpid()%2==0){
  			acumulado=getpid()+pid6+10;
  			printf("Mi pid2 es %d y el acumulado es %d \n", getpid(), acumulado);
  		}else{
  			acumulado=getpid()+pid6-100;
  			printf("Mi pid2 es %d y el acumulado es %d \n", getpid(), acumulado);
  		}
  	}
  	
  }else{
  	pid3=fork();
  	if(pid3==0){
	pid4=fork();
	  	if(pid4==0){
	  		if(getpid()%2==0){
	  			acumulado=pid3+getpid()+pid6+10;
	  			printf("Mi pid4 es %d y el acumulado es %d \n", getpid(), acumulado);
	  		}else{
	  			acumulado=pid3+getpid()+pid6-100;
	  			printf("Mi pid4 es %d y el acumulado es %d \n", getpid(), acumulado);
	  		}
	  		
	  	}else{
	  	wait(NULL);
	  		if(getpid()%2==0){
	  			acumulado=getpid()+pid6+10;
	  			printf("Mi pid3 es %d y el acumulado es %d \n", getpid(), acumulado);
	  		}else{
	  			acumulado=getpid()+pid6-100;
	  			printf("Mi pid3 es %d y el acumulado es %d \n", getpid(), acumulado);
	  		}
	  	}
  	}else {
  		wait(NULL);
  		wait(NULL);	
  	}
  }
  	
exit(0);
  	
}
