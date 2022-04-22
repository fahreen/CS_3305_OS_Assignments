#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int main (){
	pid_t i, j, pid1, pid2, pid11;
	pid1 = fork();

	if (pid1 < 0){
		printf("fork unsuccessful");
		exit(1);}

	if (pid1 >0){
		i = getpid();
		j = pid1;
		printf("\nparent process(PID %d) created child_1(PID %d)\n", i,j);
		printf("\nparent process(PID %d) is waiting for  child_1(PID %d) to complete before creating child_2\n", i,j);
		
		/* wait for child one to create another child and terminate*/
		wait(NULL);

		/*create second child*/
		pid2 = fork();
}

  /*child one */
        if (pid1 == 0){
                i = getppid();
                j = getpid();
		pid2= -1;
                pid11 = fork();
        if (pid11 > 0){
                i = getpid();
                j = pid11;
                printf("\nchild_1(PID %d) created child_1.1 (PID %d)",i, j);
                printf("\nchild 1(PID %d) is now  completed", i);
		pid2= -1;        
}

        }

		/* make sure parent is not destroyed*/
		if (pid2 >0){
			wait(NULL);}
	
		if (pid2 == 0){
			i = getppid();
			j = getpid();
			printf("\nparent (PID %d) created child_2 (PID %d)\n", i, j);
			printf("\nchild_2 (PID %d) is calling an external program and leaving child_2...\n", j);
		
			/* call external program with excel*/
			execl( "external_program.out", NULL);
	}

}


