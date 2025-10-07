#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void main() {
	int fd1[2], fd2[2];

	pid_t pid;

	pipe(fd1);
	pipe(fd2);
	int num1,dni;
	char letra[] = "TRWAGMYFPDXBNJZSQVHLCKE";
	
	
	pid=fork();
	if(pid==0){
		close(fd1[0]);
		close(fd2[1]);
		
		printf("Introduce el número de tu DNI: \n");
		scanf("%d", &num1);
		
		write(fd1[1], &num1, sizeof(num1));
		
		
		read(fd2[0], &dni, sizeof(dni));
		printf("La letra del NIF es %c",letra[dni]);
		
			
	}else{
		close(fd1[1]);
		close(fd2[0]);
			
		read(fd1[0], &num1, sizeof(num1));
		
		dni = num1;
		dni %= 23;
		
		write(fd2[1], &dni, sizeof(dni));
		wait(NULL);
	}
exit(0);
}
