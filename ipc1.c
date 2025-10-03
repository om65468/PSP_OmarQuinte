#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

void main() {
	int fd[2];
	
	time_t tim;
	char*fecha;
	char buffer[100];
	
	pid_t pid;
	pipe(fd);
	
	pid=fork();
	if(pid==0){
		close(fd[1]);
		read(fd[0], buffer, sizeof(buffer));
		printf("Soy el proceso hijo con pid %d, y tiempo %s", getpid(), buffer);
		
	}else{
		time(&tim);
		fecha = ctime(&tim) ;
		
		close(fd[0]);
		write(fd[1], fecha, strlen(fecha)+1);
		close(fd[1]);
		wait(NULL);
	}

exit(0);
}
