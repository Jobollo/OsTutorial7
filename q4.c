#include <stdio.h>
#include  <sys/types.h>
#include  <signal.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>


int main( void ) {
	char *argv[3] = {"Command-line", ".", NULL};

	pid_t pid = fork();
	if ( pid == 0 ) {
		static char *argv[]={NULL};
		execv("process", argv );
		exit(1);
	}
		
	
	sleep(5);
	kill(pid, SIGINT);
	signal(pid,SIGTSTP);
	sleep(10);
	signal(pid,SIGCONT);
	wait(5);
	return 0;
}
