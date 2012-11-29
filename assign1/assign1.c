// z1297066

#include <stdio.h>
#include <unistd.h>

void main() {
	
	pid_t pid = fork(); // fork & create child process
	
	// error occured
	if(pid < 0) {
	
		printf("Error.");
	
	} else if(pid == 0) { // child process
		
		// print out process id's
		printf("In child: My PID = %d, my parent PID = %d.\n", getpid(), getppid());
	
		// create null terminated string
		char *const args[] = {"ps", "-fU", "z1297066", NULL};
		
		// replace current process with provided arg
		execv("/bin/ps", args);
		
		// wait for child process to finish
		wait(3);
		
	} else { // parent process
	
		// print out process id's
		printf("In parent: Child PID = %d, my PID = %d, my parent PID = %d.\n", pid, getpid(), getppid());
	
	}
	
} // end main
