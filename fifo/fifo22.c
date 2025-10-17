#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
  int  fp, fp2,num1, cont, total,bytesleidos;
  char buffer[10];
  char buffer2[1000];

   mkfifo("FIFO2", 0666);
  
   while (1)
	{
	fp = open("FIFO2", 0);
	bytesleidos=read(fp,buffer,sizeof(buffer) - 1) ; 
	close(fp);
     if (bytesleidos > 0) {
      buffer[bytesleidos] = '\0';
      num1 = atoi(buffer); 
      
      cont=0;
	total=1;
	while(num1>cont){
		total=total*(num1-cont);
		cont++;
	}
	
	sprintf(buffer2, "%d", total);


      fp2 = open("FIFO2", 1);
      write(fp2, buffer2, strlen(buffer2) + 1);  
      close(fp2);
    }
  }
	 
   
return 0; 
}
