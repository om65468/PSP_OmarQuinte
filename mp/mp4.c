//A) se imprime primero CCC, luego se gcrea un hijo. El padre escribirá AAA y el hijo BBB

//1000: CCC
//1000: AAA
//1001: BBB

//b)
//puede salir 2 opciones: 
//CCC		1000:CCC
//AAA		1001:BBB
//BBB    	1000:AAA 
//Solo hay 2 opciones ya que el CCC esta antes del fork por lo que solo puede estar alli

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void main()
{
 printf("CCC \n");
 if (fork()==0)
 {
 	printf("BBB \n");
 } else{
 	wait(NULL);
 	printf("AAA \n");
 }
 exit(0);
}

