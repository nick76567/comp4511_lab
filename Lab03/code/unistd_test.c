#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	pid_t pid = fork();
	int status;

	if(pid == 0){
		printf("child branch\n");
		sleep(5);
	}else{
		printf("child pid %d is started\n", pid);
		wait(&status);
		printf("child pid %d is terminated with status %d\n", pid, status);
		//printf("child pid %d is terminated with status %d\n", wait(&status), status);
		//return startus 4196176
		printf("myshell is terminated with pid %d\n", getpid());
	}

	return 0;
}