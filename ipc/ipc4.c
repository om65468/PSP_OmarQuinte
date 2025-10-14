#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

void main() {
	int fd1[2], fd2[2];

	pid_t pid;

	pipe(fd1);
	pipe(fd2);
	int num1, cont, total;
	time_t t;
	
	
	pid=fork();
	if(pid==0){
		close(fd1[1]);
		close(fd2[0]);
		read(fd1[0], &num1, sizeof(num1));
		cont=0;
		total=1;
		while(num1>cont){
			total=total*(num1-cont);
			cont++;
		}
		
		write(fd2[1], &total, sizeof(total));
		
			
	}else{
		close(fd1[0]);
		close(fd2[1]);
		srand((unsigned) time(&t));
		num1=(rand()%10);
		printf("El proceso padre genera el numero %d en el pipe1 \n",num1);
		write(fd1[1], &num1, sizeof(num1));
		
		read(fd2[0], &total, sizeof(total));
		printf("El factorial calculado por el proceso hijo: %d != %d \n",num1, total);
		wait(NULL);
	}

exit(0);
}
