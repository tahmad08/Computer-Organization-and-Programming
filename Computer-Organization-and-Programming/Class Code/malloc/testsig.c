#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sigcatcher(int);
void sigexiter(int);
void sleep(unsigned int);
int getpid(void);

int main(int argc, char *argv[]) {

	signal(SIGINT, sigcatcher);
	signal(SIGQUIT, sigcatcher);
	signal(SIGTERM, sigexiter);

	printf("My process id is %d\n", getpid());
	while (1) {
		printf("Waiting 30 seconds on a signal\n");
		sleep(30);
	}
}


void sigcatcher(int s) {
	signal(s, sigcatcher);

	printf("Caught signal %d\n", s);
}

void sigexiter(int s) {
	printf("Exiting on signal %d\n", s);
	exit(1);
}

