#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

void main() {
  pid_t pid, Hijo_pid;
  
  pid=fork();
  if(pid==0){
	printf("Mi nombre es Omar \n");  
  }else{
	Hijo_pid=wait(NULL);
	printf("El pid del hijo es %d y el pid del padre es %d \n" ,pid ,getpid());
  }
  exit(0);
  }
  
