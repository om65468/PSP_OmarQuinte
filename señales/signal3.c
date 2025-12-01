#include <stdio.h>
#include <time.h>
#include <string.h>
#include <signal.h>

FILE *archivo;


void senal(int signum){
  time_t t;
  struct tm *tiempo;
  char tiempo2[10];
  time(&t);
  tiempo=localtime(&t);
  
  strftime(tiempo2, sizeof(tiempo2), "%H:%M:%S", tiempo);
  
  
  fprintf(archivo,"Señal SIGINT recibida a las %s \n", tiempo2);
  fflush(archivo);
  
}

int main(){
    archivo = fopen("salidas.txt", "a");
    
    
    pid_t pid;
    pid=getpid(); 
    signal(SIGINT,senal); 
    while (1) {
        sleep(1);
    }
    fclose(archivo);
  return 0;
}
