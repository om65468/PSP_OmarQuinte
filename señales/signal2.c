#include<stdio.h>
#include<unistd.h>
#include<signal.h>

int cont=0;

void senal(int signum){ 
  cont+=5;
  printf("Han transcurrido %d \n",cont);
  
}

int main(){
    pid_t pid;
    pid=getpid(); 
    signal(SIGUSR1,senal); 
    while (1) {
        sleep(5);
        kill(pid, SIGUSR1);
    }
  return 0;
}
