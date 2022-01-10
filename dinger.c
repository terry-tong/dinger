/*
Terry Tong
Dinger
*/

#include<signal.h>
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

static void dinger(int);

int main(void) {
	pid_t pid;
	int status;
	
	if ((pid = fork()) < 0) {
		perror("Can't fork\n");
		return 1;
	}
	if (pid == 0) {   // child process
		printf("Alarm app starting\n");
		printf("Waiting for the alarm to sound....\n\n");
		sleep(5);
		kill(pid, SIGALRM);
	}
	else if (pid > 0) {   //parent process
		signal(SIGALRM, dinger);
		waitpid(pid, &status, 0); //wait for child
	}
	else {
		fprintf(stderr, "Error forking\n");
		return 1;
	}
	printf("Done.\n");
	return 0;
}

static void dinger(int sign) {
	if (sign == SIGALRM) {
		printf("Ding!\n");
	}
	else {
		printf("False alarm!\n");
	}
}
