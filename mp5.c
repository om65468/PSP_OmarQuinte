//1000: AAA
//1001: BBB
//1002: CCC
//1000: CCC

//hay un padre (1000) y dos hijos 
//Salidas:
//AAA	AAA	AAA
//BBB	CCC	CCC
//CCC	BBB	CCC
//CCC	CCC	BBB

//Solo esas formas por que el momento en que se ejecutan esos procesos es aleatoria

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
void main()
{
 pid_t pid1, pid2;
 printf("AAA \n");
 pid1 = fork();
 if (pid1==0)
 {
 	printf("BBB \n");
 }
 else
 {
 	pid2 = fork();
 	if(pid2==0){
 		printf("CCC \n");
 	}else{
 		wait(NULL);
 		wait(NULL);
 		printf("CCC \n");
 	}
 	
 }
 exit(0);
}

