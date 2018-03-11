#include <stdio.h>
#include  <sys/types.h>
#include  <signal.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>

void SIGINT_handler(int);

int main( void ) {
	char *argv[3] = {"Command-line", ".", NULL};

	pid_t pid = fork();
	
	if (signal(SIGINT, SIGINT_handler) == SIG_ERR) {
		printf("SIGINT install error\n");
		exit(1);
	}
	if ( pid == 0 ) {
		static char *argv[]={NULL};
		execv("process", argv );
		exit(1);
	}
		
	
	sleep(5);
	kill(pid, SIGINT);
	wait( 2 );
	return 0;
}

void SIGINT_handler(int sig)
{
	signal(sig, SIG_IGN);
	printf("From SIGINT: just got a %d (SIGINT ^C) signal\n", sig);
     	signal(sig, SIGINT_handler);
}
