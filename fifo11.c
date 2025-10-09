#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

int main(void)
{
  int  fp, fp2;
  int  p, p2, num1, solucion;
  time_t t;

   p=mkfifo("FIFO1", 0666);
   p2=mkfifo("FIFO2", 0666);
   
   srand((unsigned) time(&t));
   num1=(rand()%10);
   printf("El numero es es: %d \n", num1);
   
   fp = open("FIFO1", 1);
   write(fp,&num1,sizeof(num1)); 
   close(fp);
   
   
	fp2 = open("FIFO2", 0);
	read(fp2,&solucion,sizeof(solucion)); 
	close(fp2); 
	printf("El resultado es: %d \n", solucion);

	remove("FIFO1");
	remove("FIFO2");
   return 0; 
}
