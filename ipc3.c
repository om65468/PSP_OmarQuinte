#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

void main() {
	int fd[2];
	pid_t pid;
	pipe(fd);
	int num1, num2, total=0;
	time_t t;
	
	
	pid=fork();
	if(pid!=0){
		close(fd[1]);
		
		read(fd[0], &num1, sizeof(num1));
		read(fd[0], &num2, sizeof(num2));
		
		total=num1+num2;
		printf("%d + %d= %d \n",num1, num2, total);
		total=num1-num2;
		printf("%d - %d= %d \n",num1, num2, total);
		total=num1*num2;
		printf("%d * %d= %d \n",num1, num2, total);
		total=num1/num2;
		printf("%d / %d= %d \n",num1, num2, total);
			
	}else{
		close(fd[0]);
		srand((unsigned) time(&t));
		num1=(rand()%50);
		num2=(rand()%50);
		write(fd[1], &num1, sizeof(num1));
		write(fd[1], &num2, sizeof(num2));
		close(fd[1]);
		wait(NULL);
	}

exit(0);
}
