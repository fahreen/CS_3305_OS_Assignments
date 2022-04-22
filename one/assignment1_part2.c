#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
	
	pid_t pid, i,j;
	int x, y, z;
	
	int fd[2];
	if (pipe(fd) <0){
		perror("pipe error");
		exit(0);}
	
	
	/*else{
		i = getpid();
		printf("\n A pipe is created for communication between parent (PID %d) and child" , i);
	}*/
	pid = fork();
	if (pid > 0){
		
		i = getpid();
		j = pid;
		printf("\n A pipe is created for communication between parent (PID %d) and child" , i);
		printf("\n parent (PID %d) created a child (PID %d) ", i,j);
		x = atoi(argv[1]);
		printf(" \n parent (PID %d) Reading X = %d  from the user", i,x);
		wait (NULL);
		read(fd[0], &y, (sizeof(y) +1)); 
		printf("\n parent (PID = %d) Reading Y from the pipe (Y = %d)", i, y);
		z = x+y;
		printf("\n parent (PID = %d) adding  X + Y  = %d ", i, z);

	}
	
	if (pid ==0){
		j = getpid();
		y= atoi(argv[2]);
		printf("\n child (PID %d) Reading Y = %d  from the user ", j,y);
		write (fd[1], &y, sizeof(y)); 
		printf("\n child (PID %d) writing Y into the pipe \n", j); // why do i need a \n here
}
return 0;
}
