#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>




void alarm_function(){
	printf("--- Alarm is on ---\n");
	alarm(2);
	 for(int i=1;;i++){
    sleep(1);  // Delay for 1 second
	}
}

void Bad_memory_access()
{ 	
    FILE *f = tmpfile();
    int *m = (int*)mmap(0, 4, PROT_WRITE, MAP_PRIVATE, fileno(f), 0);
    *m = 0;
}

void press_CtrlC(){
	while (1)
	{
		printf("          ***** Please press Ctrl+C *****\n");
		sleep(1.5);
	}
}

void press_CtrlZ(){
	while (1)
	{
		printf("          ***** Please press Ctrl+Z *****\n");
		sleep(1.5);
	}
}




void sig_handler(int signum)
{
	int i=5;
	int j=0;
	int k;
	switch (signum) {
		case SIGCHLD:
			printf(">> SIGCHLD: Child process terminated.\n");
			printf("------------------------------------------------\n");
			raise(SIGUSR1);
			printf("This line shouldn't be printed\n");

		case SIGUSR1: 
			printf(">> SIGUSR1: User-defined signal 1.\n");
			printf("------------------------------------------------\n");
			k=i/j;
			printf("This line shouldn't be printed");
		
		case SIGFPE:
			printf(">> SIGFPE: Erroneous arithmetic operation.\n");
			printf("------------------------------------------------\n");
			abort();
			printf("This line shouldn't be printed\n");
		
		case SIGABRT:
			printf(">> SIGABRT: Process abort signal.\n");
			printf("------------------------------------------------\n");
			alarm_function();
			printf("This line shouldn't be printed\n");
		
		case SIGALRM:
			printf(">> SIGALRM: Alarm clock.\n");
			printf("------------------------------------------------\n");
			Bad_memory_access();
			printf("This line shouldn't be printed\n");
		
		case SIGSEGV:
			printf(">> SIGSEGV: Invalid memory reference.\n");
			printf("------------------------------------------------\n");
			press_CtrlZ();
			printf("This line shouldn't be printed\n");

		case SIGTSTP:
			printf(">> SIGTSTP: Terminal stop signal.\n");
			printf("------------------------------------------------\n");
			press_CtrlC();
			printf("This line shouldn't be printed\n");

		case SIGINT:
			printf("\n>> SIGINT: Terminal interrupt signal.\n");
			printf("------------------------------------------------\n");
			kill(getpid(), SIGQUIT);
			printf("This line shouldn't be printed\n");

		case SIGQUIT:
			printf(">> SIGQUIT: Terminal quit signal.\n");
			printf("------------------------------------------------\n");
			exit(143);
			printf("This line shouldn't be printed\n");
	}
}


int main()
{
	signal (SIGCHLD, sig_handler);
	signal (SIGUSR1, sig_handler);
	signal (SIGFPE, sig_handler);
	signal (SIGABRT, sig_handler);
	signal (SIGALRM, sig_handler);
	signal (SIGINT, sig_handler);
	signal (SIGSEGV, sig_handler);
	signal (SIGQUIT, sig_handler);
	signal (SIGTSTP, sig_handler);

	printf("\n");
	if (!(fork())) {
		exit(1);
	}
	wait(NULL);

}