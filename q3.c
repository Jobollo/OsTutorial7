#include <stdio.h>
#include  <sys/types.h>
#include  <signal.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>

/* This program forks and and the prints whether the process is
 *   - the child (the return value of fork() is 0), or
 *   - the parent (the return value of fork() is not zero)
 *
 * When this was run 100 times on the computer the author is
 * on, only twice did the parent process execute before the
 * child process executed.
 *
 * Note, if you juxtapose two strings, the compiler automatically
 * concatenates the two, e.g., "Hello " "world!"
 */

void SIGINT_handler(int);

int main( void ) {
	char *argv[3] = {"Command-line", ".", NULL};

	int pid = fork();
	int ppid;
	gid_t gid;
	
	if (signal(SIGINT, SIGINT_handler) == SIG_ERR) {
		printf("SIGINT install error\n");
		exit(1);
	}
	if ( pid == 0 ) {
		execvp("process", argv );	
	}
	
	if ((pid = getpid()) < 0) {
	  perror("unable to get pid\n");
	} else {
	  printf("The process id is %d\n", pid);
	}

	/* get the parent process id */
	if ((ppid = getppid()) < 0) {
	  perror("unable to get the ppid\n");
	} else {
	  printf("The parent process id is %d\n", ppid);
	}

	/* get the group process id */
	if ((gid = getgid()) < 0) {
	  perror("unable to get the group id\n");
	} else {
	  printf("The group id is %d\n", gid);
	}	
	
	sleep(5);
	kill(pid, SIGINT);
	/* Put the parent to sleep for 2 seconds--let the child finished executing */
	wait( 2 );


	return 0;
}

void SIGINT_handler(int sig)
{
	signal(sig, SIG_IGN);
	printf("From SIGINT: just got a %d (SIGINT ^C) signal\n", sig);
     	signal(sig, SIGINT_handler);
}
