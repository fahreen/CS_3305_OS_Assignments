#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>

int z;
void *thread_set_z(void *num1){
	int *x = (int*) num1;
	//int *y = (int*) num2;
	//int *z = (int*) num3
	z = (*x )+ z;
	return 0;
	};

int main(){
	
	int x, y;
	pid_t pid;
	x= 10;
	y= 20;
	z = 0;
	pthread_t thread_1, thread_2;
	pid = fork();
	
	if(pid <0){
		printf("Fork Unsuccessful");
		exit(1);
		}
	if (pid >0){
		wait(NULL);
		printf("Fork z = %d\n" , z);
		pthread_create( &thread_1, NULL, thread_set_z, &x);
		pthread_create( &thread_2, NULL, thread_set_z, &y);
		pthread_join (thread_1, NULL);
		pthread_join (thread_2, NULL);
		printf("Thread z = %d\n", z);
		}
	
	if (pid ==0){
		z = x+y;}
		
return 0;
};

