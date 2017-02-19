// wait(...)
// Author: Nick Wong
// Date: 19-Feb-2017
// Content:
// bug.
	if(strcmp(cmdline, "exit") == 0){
		printf("myshell is terminated with pid %d\n", getpid());
		exit(0);
	}
	if(pid == 0){
		printf("child pid %d is started\n", getpid());
		sleep(seconds);
		printf("child pid %d is terminated with status %d\n", getpid(), status);
	}else if(pid > 0){
		wait(&status);
	}
// solve.
	if(strcmp(cmdline, "exit") == 0){
		printf("myshell is terminated with pid %d\n", getpid());
		exit(0);
	}
	if(pid == 0){
		printf("child pid %d is started\n", getpid());
		sleep(seconds);
		printf("child pid %d is terminated with status %d\n", getpid(), status);
		exit(0);
	}else if(pid > 0){
		wait(&status);
	}
// Problem
// After fork() has been called and parent calls the wait(...)
// go to child process
// in this task, it is the function in the child process
// so after return from the function to main function
// it is still in the child process' while loop
// so we have to explicitly call the exit(0) in child process
// go back to parent
