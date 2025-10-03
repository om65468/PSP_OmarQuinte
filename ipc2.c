#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

void main() {
	int fd[2];
	
	pid_t pid;
	pipe(fd);
	int num1, num2, num3, total=0;
	char sum;
	
	pid=fork();
	if(pid==0){
		close(fd[1]);
		
		read(fd[0], &num1, sizeof(num1));
		read(fd[0], &num2, sizeof(num2));
		read(fd[0], &num3, sizeof(num3));
		read(fd[0], &sum, sizeof(sum));
		
		printf("Numero a sumar: %d \n",num1);
		printf("Numero a sumar: %d \n",num2);
		printf("Numero a sumar: %d \n",num3);
		printf("Recibido %c \n",sum);
		total=num1+num2+num3;
		printf("Suma total es: %d \n",total);
			
	}else{
		close(fd[0]);
		num1=16;
		num2=23;
		num3=15;
		sum='+';
		write(fd[1], &num1, sizeof(num1));
		write(fd[1], &num2, sizeof(num2));
		write(fd[1], &num3, sizeof(num3));
		write(fd[1], &sum, sizeof(sum));
		
		close(fd[1]);
		wait(NULL);
	}

exit(0);
}
