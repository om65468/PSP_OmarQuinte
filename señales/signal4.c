#include <stdio.h>
#include <time.h>
#include <string.h>
#include <signal.h>

int num1, num2;

void senal(int signum){
  time_t t;
  struct tm *tiempo;
  char tiempo2[10];
  int cont=0;
  
  printf("Alarma activada \n");
  
  while(num1>cont){
  time(&t);
  tiempo=localtime(&t);
  
  strftime(tiempo2, sizeof(tiempo2), "%H:%M:%S", tiempo);
  printf("Señal de alarma recibida a las %s \n", tiempo2);
  cont++;
  sleep(num2);
  }
  
  printf("Alarma desactivada \n");
  
}

int main(){
    pid_t pid;
    pid=getpid();
    printf("¿Cuántas veces sonará la alarma?:");
    scanf("%d", &num1);
    
    printf("¿Cada cuántos segundos se repetirá la alarma?:");
    scanf("%d", &num2);
    
    signal(SIGUSR1,senal); 
    kill(pid, SIGUSR1);
    
  return 0;
}
