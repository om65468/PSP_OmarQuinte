#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

int main(void)
{
  char buffer[10];
  char buffer2[1000];
  int  num1, fp, fp2,bytesleidos;
  time_t t;

   mkfifo("FIFO2", 0666);
   
   srand((unsigned) time(&t));
   num1=(rand()%10);
   
   printf("El numero es: %d \n", num1);
   fp=open("FIFO2", 1);
   
   sprintf(buffer, "%d", num1);
   
   write(fp, buffer,strlen(buffer)+1);
   close(fp2);

 
  fp2=open("FIFO2", 0);
  bytesleidos = read(fp2, buffer2, sizeof(buffer2) - 1);  
  if (bytesleidos > 0) {
    buffer2[bytesleidos] = '\0';
    printf("El resultado recibido es: %s\n", buffer2);
  }  
  close(fp2);
  remove("FIFO2");
   return 0;
}
