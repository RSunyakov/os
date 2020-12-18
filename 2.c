#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <time.h>


int main (int argc, char *argv[]) {
	pid_t childpid;
	time_t secs = time(0);
	struct tm *local = localtime(&secs);
	char timeString[8];

	if ((childpid = fork()) <= 0) {  
                
	}
	if (childpid > 0) {
	if ((childpid = fork()) <= 0) 
		 while (wait(NULL) > -1 || errno != ECHILD)
                break;
	}
	printf("process ID:%ld parent ID:%ld %02d:%02d:%02d \n", (long)getpid(), (long)getppid(), local->tm_hour, local->tm_min, local->tm_sec);
	
	if (childpid > 0) {
	system("ps -x");
	}
	return 0;
}
