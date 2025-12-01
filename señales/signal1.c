#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include <time.h>

time_t fin;
struct tm *final;

void senal(int signum){ 
  time(&fin);
  final = localtime(&fin);
  
  printf("Fin del proceso %d",getpid());
  fecha(final);
  signal(SIGINT,SIG_DFL);   
  
}

void fecha(struct tm *t) {
    printf("%02d/%02d/%04d %02d:%02d:%02d\n",
           t->tm_mday, t->tm_mon + 1, t->tm_year + 1900,
           t->tm_hour, t->tm_min, t->tm_sec);
}


int main(){
    
    time_t inicio;
    struct tm *ini;
    
    time(&inicio);
    ini = localtime(&inicio);
    
    printf("Inicio del proceso %d:",getpid());
    fecha(ini);
    
    signal(SIGINT,senal);
    
    while (1) {
        sleep(2);
    }
        
  return 0;
}
