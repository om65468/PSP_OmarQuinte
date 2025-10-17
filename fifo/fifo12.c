#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
  int  fp, fp2;
  int  p, p2, num1, cont, total;

   p=mkfifo("FIFO1", 0666);
   p2=mkfifo("FIFO2", 0666);
   
  
	fp = open("FIFO1", 0);
	read(fp,&num1,sizeof(num1)); 
	close(fp);

	cont=0;
	total=1;
	while(num1>cont){
		total=total*(num1-cont);
		cont++;
	}

	fp2 = open("FIFO2", 1);
	write(fp2,&total,sizeof(total)); 
	
	close(fp2);
	 
	 remove("FIFO1");
	 remove("FIFO2");
   
return 0; 
}

