#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

int num1, lee;

int fd[2];
pid_t pid, pid2, prim, seg;

void senal(int signum){
  char buffer[10];
  lee=read(fd[0], buffer, sizeof(buffer)-1);
  buffer[lee] = '\0';
  num1=atoi(buffer);
  printf("Número par %d recibido por el proceso P2 con pid %d \n",num1 , getpid());
}

void senal2(int signum){
  char buffer[10];
  lee=read(fd[0], buffer, sizeof(buffer)-1);
  buffer[lee] = '\0';
  num1=atoi(buffer);
  printf("Número par %d recibido por el proceso P3 con pid %d\n",num1 , getpid());
}

int main(){
    
    pipe(fd);

    
    pid=fork();
    
    if(pid==0){
    	close(fd[1]);
    	signal(SIGUSR1,senal); 
    	prim=getpid();
    	while (1) {
		pause();
	    }
    } else{
    
    pid2=fork();
    
    	
    if (pid2==0){
		close(fd[1]);
		signal(SIGUSR2,senal2); 
		seg=getpid();
		while (1) {
		pause();
	    }
	}
    
    if(pid!=0){
    close(fd[0]);
    	do{
	    	printf("Introduce número:");
	    	scanf("%d", &num1);
	    	if(num1==0){
	    		kill(pid, SIGTERM);
	    		printf("Mandando señal de terminación al proceso hijo P2 con pid %d\n", prim);
                    	kill(pid2, SIGTERM);
                    	printf("Mandando señal de terminación al proceso hijo P3 con pid %d\n", seg);
	    		break;
	    	}
	    	char buffer[10];
	    	sprintf(buffer, "%d", num1);
	    	write(fd[1], buffer,strlen(buffer)+1);
	    	
	    	if(num1%2==0){
	    		
	    		kill(pid, SIGUSR1);
	    	} else {
	    		kill(pid2, SIGUSR2);
	    	}
		sleep(0.3);
	    } while(num1!=0);
    }
    
    printf("Fin proceso padre con pid %d", getpid())
    }
    
  return 0;
}
